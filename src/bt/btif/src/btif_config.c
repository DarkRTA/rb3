/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/************************************************************************************
 *
 *  Filename:      btif_config.c
 *
 *  Description:   Stores the local BT adapter and remote device properties in
 *                 NVRAM storage, typically as xml file in the
 *                 mobile's filesystem
 *
 *
 ***********************************************************************************/
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <private/android_filesystem_config.h>

#define LOG_TAG "btif_config"

#include <hardware/bluetooth.h>
#include "btif_api.h"
#include "btif_config.h"
#include "btif_config_util.h"
#include "btif_sock_thread.h"
#include "btif_sock_util.h"
#include "btif_util.h"

//#define UNIT_TEST
#define CFG_PATH "/data/misc/bluedroid/"
#define CFG_FILE_NAME "bt_config"
#define CFG_FILE_EXT ".xml"
#define CFG_FILE_EXT_OLD ".old"
#define CFG_FILE_EXT_NEW ".new"
#define CFG_GROW_SIZE (10*sizeof(cfg_node))
#define GET_CHILD_MAX_COUNT(node) (short)((int)(node)->bytes / sizeof(cfg_node))
#define GET_CHILD_COUNT(p) (short)((int)(p)->used / sizeof(cfg_node))
#define ADD_CHILD_COUNT(p, c) (p)->used += (short)((c)*sizeof(cfg_node))
#define DEC_CHILD_COUNT(p, c) (p)->used -= (short)((c)*sizeof(cfg_node))
#define GET_NODE_COUNT(bytes) (bytes / sizeof(cfg_node))
#define GET_NODE_BYTES(c) (c * sizeof(cfg_node))
#define MAX_NODE_BYTES 32000
#define CFG_CMD_SAVE 1

#ifndef FALSE
#define TRUE 1
#define FALSE 0
#endif
typedef struct cfg_node_s
{
    const char* name;
    union
    {
        struct cfg_node_s* child;
        char* value;
    };
    short bytes;
    short type;
    short used;
    short flag;
} cfg_node;

static pthread_mutex_t slot_lock;
static int pth = -1; //poll thread handle
static cfg_node root;
static int cached_change;
static int processing_save_cmd;
static void cfg_cmd_callback(int cmd_fd, int type, int flags, uint32_t user_id);
static inline short alloc_node(cfg_node* p, short grow);
static inline void free_node(cfg_node* p);
static inline void free_inode(cfg_node* p, int child);
static inline short find_inode(const cfg_node* p, const char* name);
static cfg_node* find_node(const char* section, const char* key, const char* name);
static int remove_node(const char* section, const char* key, const char* name);
static int remove_filter_node(const char* section, const char* filter[], int filter_count, int max_allowed);
static inline cfg_node* find_free_node(cfg_node* p);
static int set_node(const char* section, const char* key, const char* name,
                        const char* value, short bytes, short type);
static int save_cfg();
static void load_cfg();
static short find_next_node(const cfg_node* p, short start, char* name, int* bytes);
static int create_dir(const char* path);
#ifdef UNIT_TEST
static void cfg_test_load();
static void cfg_test_write();
static void cfg_test_read();
#endif
#define MY_LOG_LEVEL appl_trace_level
#define MY_LOG_LAYER TRACE_LAYER_NONE | TRACE_ORG_APPL

static inline void dump_node(const char* title, const cfg_node* p)
{
    if(p) {
        bdld("%s, p->name:%s, child/value:%p, bytes:%d",
                          title, p->name, p->child, p->bytes);
        bdld("p->used:%d, type:%x, p->flag:%d",
                          p->used, p->type, p->flag);
    } else bdld("%s is NULL", title);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
int btif_config_init()
{
    static int initialized;
    bdld("in initialized:%d", initialized);
    if(!initialized)
    {
        initialized = 1;
        struct stat st;
        if(stat(CFG_PATH, &st) != 0)
            bdle("%s does not exist, need provision", CFG_PATH);
        btsock_thread_init();
        init_slot_lock(&slot_lock);
        lock_slot(&slot_lock);
        root.name = "Bluedroid";
        alloc_node(&root, CFG_GROW_SIZE);
        dump_node("root", &root);
        pth = btsock_thread_create(NULL, cfg_cmd_callback);
        load_cfg();
        unlock_slot(&slot_lock);
        #ifdef UNIT_TEST
            cfg_test_write();
            //cfg_test_read();
            exit(0);
        #endif
    }
    return pth >= 0;
}
int btif_config_get_int(const char* section, const char* key, const char* name, int* value)
{
    int size = sizeof(*value);
    int type = BTIF_CFG_TYPE_INT;
    return btif_config_get(section, key, name, (char*)value, &size, &type);
}
int btif_config_set_int(const char* section, const char* key, const char* name, int value)
{
    return btif_config_set(section, key, name, (char*)&value, sizeof(value), BTIF_CFG_TYPE_INT);
}
int btif_config_get_str(const char* section, const char* key, const char* name, char* value, int* size)
{
    int type = BTIF_CFG_TYPE_STR;
    if(value)
        *value = 0;
    return btif_config_get(section, key, name, value, size, &type);
}
int btif_config_set_str(const char* section, const char* key, const char* name, const char* value)
{
   value = value ? value : "";
   return btif_config_set(section, key, name, value, strlen(value) + 1, BTIF_CFG_TYPE_STR);
}
int btif_config_exist(const char* section, const char* key, const char* name)
{
    int ret = FALSE;
    if(section && *section && key && *key)
    {
        lock_slot(&slot_lock);
        ret = find_node(section, key, name) != NULL;
        unlock_slot(&slot_lock);
    }
    return ret;
}
int btif_config_get(const char* section, const char* key, const char* name, char* value, int* bytes, int* type)
{
    int ret = FALSE;
    bdla(section && *section && key && *key && name && *name && bytes && type);
    bdld("section:%s, key:%s, name:%s, value:%p, bytes:%d, type:%d",
                section, key, name, value, *bytes, *type);
    if(section && *section && key && *key && name && *name && bytes && type)
    {
        lock_slot(&slot_lock);
        const cfg_node* node = find_node(section, key, name);
        dump_node("found node", node);
        if(node)
        {
            if(*type == node->type && value && *bytes >= node->used)
            {
                if(node->used > 0)
                    memcpy(value, node->value, node->used);
                ret = TRUE;
            }
            *type = node->type;
            *bytes = node->used;
            if(ret != TRUE)
            {
                if(*type != node->type)
                    bdle("value:%s, wrong type:%d, need to be type: %d",
                                      name, *type, node->type);
                if(value && *bytes < node->used)
                    bdle("value:%s, not enough size: %d bytes, need %d bytes",
                                      name, node->used, *bytes);
            }
        }
        unlock_slot(&slot_lock);
    }
    return ret;
}
int btif_config_set(const char* section, const char* key, const char* name, const char*  value, int bytes, int type)
{
    int ret = FALSE;
    bdla(section && *section && key && *key && name && *name);
    bdla(bytes < MAX_NODE_BYTES);
    if(section && *section && key && *key && name && *name && bytes < MAX_NODE_BYTES)
    {
        lock_slot(&slot_lock);
        ret = set_node(section, key, name, value, (short)bytes, (short)type);
        if(ret && !(type & BTIF_CFG_TYPE_VOLATILE))
            cached_change++;
        unlock_slot(&slot_lock);
    }
    return ret;
}
int btif_config_remove(const char* section, const char* key, const char* name)
{
    bdla(section && *section && key && *key);
    bdld("section:%s, key:%s, name:%s", section, key, name);
    int ret = FALSE;
    if(section && *section && key && *key)
    {
         lock_slot(&slot_lock);
         ret = remove_node(section, key, name);
         if(ret)
            cached_change++;
         unlock_slot(&slot_lock);
    }
    return ret;
}

int btif_config_filter_remove(const char* section, const char* filter[], int filter_count, int max_allowed)
{
    bdla(section && *section && max_allowed > 0);
    bdld("section:%s, filter:%s, filter count:%d, max allowed:%d",
                section, filter[0], filter_count, max_allowed);
    int ret = FALSE;
    if(section && *section && max_allowed > 0)
    {
         lock_slot(&slot_lock);
         ret = remove_filter_node(section, filter, filter_count, max_allowed);
         if(ret)
            cached_change++;
         unlock_slot(&slot_lock);
    }
    return ret;
}
typedef struct {
    short si;
    short ki;
    short vi;
    short reserved;
} cfg_node_pos;
short btif_config_next_key(short pos, const char* section, char * name, int* bytes)
{
    int next = -1;
    lock_slot(&slot_lock);
    short si = find_inode(&root, section);
    if(si >= 0)
    {
        const cfg_node* section_node = &root.child[si];
        next = find_next_node(section_node, pos, name, bytes);
    }
    unlock_slot(&slot_lock);
    return next;
}
short btif_config_next_value(short pos, const char* section, const char* key, char* name, int* bytes)
{
    int next = -1;
    lock_slot(&slot_lock);
    short si = find_inode(&root, section);
    if(si >= 0)
    {
        const cfg_node* section_node = &root.child[si];
        short ki = find_inode(section_node, key);
        if(ki >= 0)
        {
            const cfg_node* key_node = &section_node->child[ki];
            next = find_next_node(key_node, pos, name, bytes);
        }
    }
    unlock_slot(&slot_lock);
    return next;
}
int btif_config_enum(btif_config_enum_callback cb, void* user_data)
{
    bdla(cb);
    if(!cb)
        return FALSE;
    lock_slot(&slot_lock);
    int si, ki, vi;
    cfg_node *section_node, *key_node, *value_node;
    for(si = 0; si < GET_CHILD_COUNT(&root); si++)
    {
        section_node = &root.child[si];
        if(section_node->name && *section_node->name)
        {
            for(ki = 0; ki < GET_CHILD_COUNT(section_node); ki++)
            {
                key_node = &section_node->child[ki];
                if(key_node->name && *key_node->name)
                {
                    for(vi = 0; vi < GET_CHILD_COUNT(key_node); vi++)
                    {
                        value_node = &key_node->child[vi];
                        if(value_node->name && *value_node->name)
                        {
                            cb(user_data, section_node->name, key_node->name, value_node->name,
                                            value_node->value, value_node->used, value_node->type);
                        }
                    }
                }
            }
        }
    }
    unlock_slot(&slot_lock);
    return TRUE;
}
int btif_config_save()
{
    lock_slot(&slot_lock);
    bdld("processing_save_cmd:%d, cached change:%d", processing_save_cmd, cached_change);
    if(!processing_save_cmd && cached_change > 0)
        btsock_thread_post_cmd(pth, CFG_CMD_SAVE, NULL, 0, 0);
    unlock_slot(&slot_lock);
    return TRUE;
}
void btif_config_flush()
{
    lock_slot(&slot_lock);
    if(cached_change > 0)
        save_cfg();
    unlock_slot(&slot_lock);
}
/////////////////////////////////////////////////////////////////////////////////////////////
static inline short alloc_node(cfg_node* p, short grow)
{
    int new_bytes = p->bytes + grow;
    if(grow > 0 && new_bytes < MAX_NODE_BYTES)
    {
        char* value = (char*)realloc(p->value, new_bytes);
        if(value)
        {
            short old_bytes = p->bytes;
            //clear to zero
            memset(value + old_bytes, 0, grow);
            p->bytes = old_bytes + grow;
            p->value = value;
            return old_bytes;//return the previous size
        }
        else bdle("realloc failed, old_bytes:%d, grow:%d, total:%d", p->bytes, grow,  p->bytes + grow);
    }
    return -1;
}
static inline void free_node(cfg_node* p)
{
    if(p)
    {
        if(p->child)
        {
            free(p->child);
            p->child = NULL;
        }
        if(p->name)
        {
            free((void*)p->name);
            p->name = 0;
        }
        p->used = p->bytes = p->flag = p->type = 0;
    }
}
static inline short find_inode(const cfg_node* p, const char* name)
{
    if(p && p->child && name && *name)
    {
        int i;
        int count = GET_CHILD_COUNT(p);
        //bdld("parent name:%s, child name:%s, child count:%d", p->name, name, count);
        for(i = 0; i < count; i++)
        {
            if(p->child[i].name && *p->child[i].name &&
                strcmp(p->child[i].name, name) == 0)
            {
                  return (short)i;
            }
        }
    }
    return -1;
}
static inline cfg_node* find_free_node(cfg_node* p)
{
    if(p && p->child)
    {
        int count = GET_CHILD_COUNT(p);
        if(count < GET_CHILD_MAX_COUNT(p))
            return  p->child + count;
    }
    return NULL;
}
static cfg_node* find_add_node(cfg_node* p, const char* name)
{
    int i = -1;
    cfg_node* node = NULL;
    if((i = find_inode(p, name)) < 0)
    {
        if(!(node = find_free_node(p)))
        {
            int old_size = alloc_node(p, CFG_GROW_SIZE);
            if(old_size >= 0)
            {
                i = GET_NODE_COUNT(old_size);
                node = &p->child[i];
                ADD_CHILD_COUNT(p, 1);
            }
        } else ADD_CHILD_COUNT(p, 1);
    }
    else node = &p->child[i];
    if(!node->name)
        node->name = strdup(name);
    return node;
}
static int set_node(const char* section, const char* key, const char* name,
                    const char* value, short bytes, short type)
{
    int si = -1, ki = -1, vi = -1;
    cfg_node* section_node = NULL;
    if((section_node = find_add_node(&root, section)))
    {
        cfg_node* key_node;
        if((key_node = find_add_node(section_node, key)))
        {
            cfg_node* value_node;
            if((value_node = find_add_node(key_node, name)))
            {
                if(value_node->bytes < bytes)
                {
                    if(value_node->value)
                        free(value_node->value);
                    value_node->value = (char*)malloc(bytes);
                    if(value_node->value)
                        value_node->bytes = bytes;
                    else
                    {
                        bdle("not enough memory!");
                        value_node->bytes = 0;
                        return FALSE;
                    }
                }
                if(value_node->value && value != NULL && bytes > 0)
                    memcpy(value_node->value, value, bytes);
                value_node->type = type;
                value_node->used = bytes;
                return TRUE;
            }
        }
    }
    return FALSE;
}
static cfg_node* find_node(const char* section, const char* key, const char* name)
{
    int si = -1, ki = -1, vi = -1;
    if((si = find_inode(&root, section)) >= 0)
    {
        cfg_node* section_node = &root.child[si];
        if(key)
        {
            if((ki = find_inode(section_node, key)) >= 0)
            {
                cfg_node* key_node = &section_node->child[ki];
                if(name)
                {
                    if((vi = find_inode(key_node, name)) >= 0)
                    {
                        return &key_node->child[vi];
                    }
                    return NULL;
                }
                return key_node;
            }
            return NULL;
        }
        return section_node;
    }
    return NULL;
}
static short find_next_node(const cfg_node* p, short start, char* name, int* bytes)
{
    bdla(0 <= start && start < GET_CHILD_COUNT(p));
    bdld("in, start:%d, child count:%d, max count:%d", start, GET_CHILD_COUNT(p), GET_CHILD_MAX_COUNT(p));
    short next = -1;
    if(name) *name = 0;
    if(0 <= start && start < GET_CHILD_COUNT(p))
    {
        int i;
        for(i = start; i < GET_CHILD_COUNT(p); i++)
        {
            cfg_node* child = &p->child[i];
            if(child->name)
            {
                int name_bytes = strlen(child->name) + 1;
                if(name && bytes && *bytes >= name_bytes)
                {
                    memcpy(name, child->name, name_bytes);
                    if(i + 1 < GET_CHILD_COUNT(p))
                        next = (short)(i + 1);
                    *bytes = name_bytes;
                }
                else if(bytes)
                {
                    *bytes = name_bytes;
                }
                break;
            }
        }
    }
    return next;
}
static void free_child(cfg_node* p, int ichild, int count)
{
    int child_count = GET_CHILD_COUNT(p);
    bdla(p && ichild + count <= child_count && count > 0);
    int icount = ichild + count;
    icount = icount <= child_count ? icount : child_count;
    int i;
    for(i = ichild; i < icount; i++)
        free_node(p->child + i);
    if(i < child_count)
    {
        int mv_count = child_count - i;
        memmove(p->child + ichild, p->child + i, GET_NODE_BYTES(mv_count));
        //cleanup the buffer of already moved children
        memset(p->child + i, 0, GET_NODE_BYTES(mv_count));
    }
    DEC_CHILD_COUNT(p, i - ichild);
}
static int remove_node(const char* section, const char* key, const char* name)
{
    short  si = -1, ki = -1, vi = -1;
    if((si = find_inode(&root, section)) >= 0)
    {
        cfg_node* section_node = &root.child[si];
        if((ki = find_inode(section_node, key)) >= 0)
        {
            cfg_node* key_node = &section_node->child[ki];
            if(name == NULL)
            {
                int count = GET_CHILD_COUNT(key_node);
                int i;
                free_child(key_node, 0, count);
                free_child(section_node, ki, 1);
                return TRUE;
            }
            else if((vi = find_inode(key_node, name)) >= 0)
            {
                free_child(key_node, vi, 1);
                return TRUE;
            }
        }
    }
    return FALSE;
}
static inline int find_first_empty(cfg_node*p, int start, int count)
{
    int i;
    for(i = start; i < count; i++)
    {
        if(p->child[i].name == NULL)
            return i;
    }
    return -1;
}
static inline int find_first_occupy(cfg_node*p, int start, int count)
{
    int i;
    for(i = start; i < count; i++)
        if(p->child[i].name)
            return i;
    return -1;
}

static void pack_child(cfg_node* p)
{
    int child_count = GET_CHILD_COUNT(p);
    int occupy = 1;
    int empty = 0;
    int i;
    for(;;)
    {
        empty = find_first_empty(p, empty, child_count);
        if(empty >= 0)
        {
            if(occupy <= empty)
                occupy = empty + 1;
            occupy = find_first_occupy(p, occupy, child_count);
            bdla(occupy != 0);
            if(occupy > 0)
            {//move
                p->child[empty] = p->child[occupy];
                memset(&p->child[occupy], 0, sizeof(cfg_node));
                empty++;
                occupy++;
            }
            else break;
        }
        else break;
    }
}
static inline int value_in_filter(cfg_node* key, const char* filter[], int filter_count)
{
    int i, j;
    int child_count = GET_CHILD_COUNT(key);
    for(i = 0; i < child_count; i++)
    {
        if(key->child[i].name && *key->child[i].name)
        {
            for(j = 0; j < filter_count; j++)
                if(strcmp(filter[j], key->child[i].name) == 0)
                    return TRUE;
        }
    }
    return FALSE;
}
static int remove_filter_node(const char* section, const char* filter[], int filter_count, int max_allowed)
{
    int  si = -1;
    if((si = find_inode(&root, section)) < 0)
    {
        bdle("cannot find section:%s", section);
        return FALSE;
    }
    cfg_node* s = &root.child[si];
    int child_count = GET_CHILD_COUNT(s);
    bdld("section:%s, curr child count:%d, filter count:%d", section, child_count, filter_count);
    if(child_count < max_allowed)
        return FALSE;
    //remove until half of max allowance left
    int total_rm = child_count - max_allowed / 2;
    int rm_count = 0;
    int i;
    for(i = 0; i < child_count; i++)
    {
        if(!value_in_filter(&s->child[i], filter, filter_count))
        {
            free_child(&s->child[i], 0, GET_CHILD_COUNT(&s->child[i]));
            free_node(&s->child[i]);
            rm_count++;
            if(rm_count >= total_rm)
                break;
        }
    }
    if(rm_count)
    {
        pack_child(s);
        DEC_CHILD_COUNT(s, rm_count);
        return TRUE;
    }
    return FALSE;
}

static int save_cfg()
{
    const char* file_name = CFG_PATH CFG_FILE_NAME CFG_FILE_EXT;
    const char* file_name_new = CFG_PATH CFG_FILE_NAME CFG_FILE_EXT_NEW;
    const char* file_name_old = CFG_PATH CFG_FILE_NAME CFG_FILE_EXT_OLD;
    int ret = FALSE;
    if(access(file_name_old,  F_OK) == 0)
        unlink(file_name_old);
    if(access(file_name_new, F_OK) == 0)
        unlink(file_name_new);
   if(btif_config_save_file(file_name_new))
    {
        cached_change = 0;
        processing_save_cmd = 0;
        chown(file_name_new, -1, AID_NET_BT_STACK);
        chmod(file_name_new, 0660);
        rename(file_name, file_name_old);
        rename(file_name_new, file_name);
        ret = TRUE;
    }
    else bdle("btif_config_save_file failed");
    return ret;
}

static int load_bluez_cfg()
{
    char adapter_path[256];
    if(load_bluez_adapter_info(adapter_path, sizeof(adapter_path)))
    {
        if(load_bluez_linkkeys(adapter_path))
            return TRUE;
    }
    return FALSE;
}
static void remove_bluez_cfg()
{
    rename(BLUEZ_PATH, BLUEZ_PATH_BAK);
}
static void clean_newline_char()
{
    char kname[128], vname[128];
    short kpos = 0;
    int kname_size, vname_size;
    vname[0] = 0;
    vname_size = sizeof(vname);
    //bdld("removing newline at the end of the adapter and device name");
    if(btif_config_get_str("Local", "Adapter", "Name", vname, &vname_size) &&
        vname_size > 2)
    {
        if(vname[vname_size - 2] == '\n')
        {
            bdld("remove newline at the end of the adapter name:%s", vname);
            vname[vname_size - 2] = 0;
            btif_config_set_str("Local", "Adapter", "Name", vname);
        }
    }
    do
    {
        kname_size = sizeof(kname);
        kname[0] = 0;
        kpos = btif_config_next_key(kpos, "Remote", kname, &kname_size);
        //bdld("Remote device:%s, size:%d", kname, kname_size);
        vname_size = sizeof(vname);
        vname[0] = 0;
        if(btif_config_get_str("Remote", kname, "Name", vname, &vname_size) &&
            vname_size > 2)
        {
            bdld("remote device name:%s", vname);
            if(vname[vname_size - 2] == '\n')
            {
                bdld("remove newline at the end of the device name:%s", vname);
                vname[vname_size - 2] = 0;
                btif_config_set_str("Remote", kname, "Name", vname);
            }
        }
     } while(kpos != -1);
}
static void load_cfg()
{
    const char* file_name = CFG_PATH CFG_FILE_NAME CFG_FILE_EXT;
    const char* file_name_new = CFG_PATH CFG_FILE_NAME CFG_FILE_EXT_NEW;
    const char* file_name_old = CFG_PATH CFG_FILE_NAME CFG_FILE_EXT_OLD;
    if(!btif_config_load_file(file_name))
    {
        unlink(file_name);
        if(!btif_config_load_file(file_name_old))
        {
            unlink(file_name_old);
            if(load_bluez_cfg() && save_cfg())
                remove_bluez_cfg();
        }
    }
    int bluez_migration_done = 0;
    btif_config_get_int("Local", "Adapter", "BluezMigrationDone", &bluez_migration_done);
    if(!bluez_migration_done)
    {
        //clean the new line char at the end of the device name. Caused by bluez config import bug
        clean_newline_char();
        btif_config_set_int("Local", "Adapter", "BluezMigrationDone", 1);
        btif_config_save();
    }
}
static void cfg_cmd_callback(int cmd_fd, int type, int size, uint32_t user_id)
{
    UNUSED(cmd_fd);
    UNUSED(size);
    UNUSED(user_id);

  //bdld("cmd type:%d, size:%d", type, size);
    switch(type)
    {
        case CFG_CMD_SAVE:
        {
            int last_cached_change = cached_change;
            processing_save_cmd = 1;
            //hold the file saving until no more change in last 3 seconds.
            bdld("wait until no more changes in short time, cached change:%d", cached_change);
            int i;
            for(i = 0; i < 100; i ++) //5 minitue max waiting
            {
                sleep(3);
                if(cached_change == 0 || last_cached_change == cached_change)
                    break;
                last_cached_change = cached_change;
            }
            bdld("writing the bt_config.xml now, cached change:%d", cached_change);
            lock_slot(&slot_lock);
            if(cached_change > 0)
                save_cfg();
            unlock_slot(&slot_lock);
            break;
        }
    }
}
#ifdef UNIT_TEST
static void cfg_test_load()
{
    load_cfg();
    char kname[128], vname[128];
    short kpos, vpos;
    int kname_size, vname_size;
    bdld("list all remote devices values:");
    kname_size = sizeof(kname);
    kname[0] = 0;
    kpos = 0;
    do
    {
        kpos = btif_config_next_key(kpos, "Remote Devices", kname, &kname_size);
        bdld("Remote devices:%s, size:%d", kname, kname_size);
        vpos = 0;
        vname[0] = 0;
        vname_size = sizeof(vname);
        while((vpos = btif_config_next_value(vpos, "Remote Devices", kname, vname, &vname_size)) != -1)
        {
            char v[128] = {0};
            int vtype = BTIF_CFG_TYPE_STR;
            int vsize = sizeof(v);
            int ret = btif_config_get("Remote Devices", kname, vname, v, &vsize, &vtype);
            bdld("btif_config_get return:%d, Remote devices:%s, value name:%s, value:%s, value size:%d, type:0x%x",
                              ret, kname, vname, v, vsize, vtype);

            vname[0] = 0;
            vname_size = sizeof(vname);
        }
        kname[0] = 0;
        kname_size = sizeof(kname);
    } while(kpos != -1);
}
static void cfg_test_write()
{
    int i;

    char key[128];
    const char* section = "Remote";
    char link_key[64];
    for(i = 0; i < (int)sizeof(link_key); i++)
        link_key[i] = i;
    bdld("[start write testing");
    if(btif_config_exist("test", "test cfg", "write"))
        return;
    btif_config_set_int("test", "test cfg", "write", 1);
    for(i = 0; i < 50; i++)
    {
        if(i % 3 == 0)
            sprintf(key, "Remote paired %d", i);
        else sprintf(key, "Remote %d", i);
        link_key[0] = i;
        btif_config_set_str(section, key, "class", "smart phone");
        if(i % 3 == 0)
        {
            if(i % 6 == 0)
                btif_config_set(section, key, "LinkKey", link_key, sizeof(link_key), BTIF_CFG_TYPE_BIN);
            else btif_config_set(section, key, "LE_KEY_LCSRK", link_key, sizeof(link_key), BTIF_CFG_TYPE_BIN);
        }
        btif_config_set_int(section, key, "count", i);
        if(!btif_config_exist(section, key, "time stamp"))
            btif_config_set_int(section, key, "time stamp", time(NULL));
    }
    static const char* exclude_filter[] =
    {"LinkKey", "LE_KEY_PENC", "LE_KEY_PID", "LE_KEY_PCSRK", "LE_KEY_LENC", "LE_KEY_LCSRK"};
    const int max_allowed_remote_device = 40;
    btif_config_filter_remove("Remote", exclude_filter, sizeof(exclude_filter)/sizeof(char*),
            max_allowed_remote_device);
    bdld("]end write testing");
    btif_config_flush();
}
static void cfg_test_read()
{
    //debug("in");
    char class[128] = {0};
    char link_key[128] = {0};
    int size, type;
    char key[128];
    const char* section;
    int ret, i;
    for(i = 0; i < 100; i++)
    {
        sprintf(key, "00:22:5F:97:56:%02d", i);
        section = "Remote";
        size = sizeof(class);
        ret = btif_config_get_str(section, key, "class", class, &size);
        bdld("btif_config_get_str return:%d, Remote devices:%s, class:%s", ret, key, class);

        size = sizeof(link_key);
        type = BTIF_CFG_TYPE_BIN;
        ret = btif_config_get(section, key, "link keys", link_key, &size, &type);
        //debug("btif_config_get return:%d, Remote devices:%s, link key:%x, %x",
        //            ret, key, *(int *)link_key, *((int *)link_key + 1));

        int timeout;
        ret = btif_config_get_int(section, key, "connect time out", &timeout);
        //debug("btif_config_get_int return:%d, Remote devices:%s, connect time out:%d", ret, key, timeout);
    }

    // debug("testing btif_config_remove");
    size = sizeof(class);
    type = BTIF_CFG_TYPE_STR;
    btif_config_set("Remote", "00:22:5F:97:56:04", "Class Delete", class, strlen(class) + 1, BTIF_CFG_TYPE_STR);

    btif_config_get("Remote", "00:22:5F:97:56:04", "Class Delete", class, &size, &type);
    // debug("Remote devices, 00:22:5F:97:56:04 Class Delete:%s", class);
    btif_config_remove("Remote", "00:22:5F:97:56:04", "Class Delete");

    size = sizeof(class);
    type = BTIF_CFG_TYPE_STR;
    ret = btif_config_get("Remote", "00:22:5F:97:56:04", "Class Delete", class, &size, &type);
    // debug("after removed, btif_config_get ret:%d, Remote devices, 00:22:5F:97:56:04 Class Delete:%s", ret, class);
    // debug("out");
}
#endif
