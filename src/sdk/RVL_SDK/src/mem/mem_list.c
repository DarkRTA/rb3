#include <revolution/MEM.h>

/**
 * Get list node from a list object
 */
#define OBJECT_GET_NODE(list, object) ((MEMLink*)((char*)object + list->offset))

void MEMInitList(MEMList* list, u16 offset) {
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->offset = offset;
}

static void SetFirstObject_(MEMList* list, void* object) {
    MEMLink* node = OBJECT_GET_NODE(list, object);
    node->next = NULL;
    node->prev = NULL;

    list->head = object;
    list->tail = object;
    list->length++;
}

void MEMAppendListObject(MEMList* list, void* object) {
    MEMLink* node;
    MEMLink* tail;

    if (list->head == NULL) {
        SetFirstObject_(list, object);
    } else {
        node = OBJECT_GET_NODE(list, object);
        node->prev = list->tail;
        node->next = NULL;

        tail = OBJECT_GET_NODE(list, list->tail);
        tail->next = object;

        list->tail = object;
        list->length++;
    }
}

void MEMRemoveListObject(MEMList* list, void* object) {
    MEMLink* node = OBJECT_GET_NODE(list, object);

    if (node->prev == NULL) {
        list->head = node->next;
    } else {
        OBJECT_GET_NODE(list, node->prev)->next = node->next;
    }

    if (node->next == NULL) {
        list->tail = node->prev;
    } else {
        OBJECT_GET_NODE(list, node->next)->prev = node->prev;
    }

    node->prev = NULL;
    node->next = NULL;

    list->length--;
}

void* MEMGetNextListObject(MEMList* list, void* object) {
    if (object == NULL) {
        return list->head;
    }

    return OBJECT_GET_NODE(list, object)->next;
}
