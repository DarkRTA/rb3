#include "net_band/DataResults.h"
#include "net/JsonUtils.h"
#include "os/Debug.h"

bool DataResult::GetDataResultValue(String str, DataNode &node) const {
    bool found = false;
    std::map<String, DataNode>::const_iterator it = mDataMap.find(str);
    if (it != mDataMap.end()) {
        found = true;
        node = it->second;
    }
    return found;
}

DataResultList::DataResultList() {
    mQDataResultString = new Quazal::String();
    mUpdated = 0;
}

DataResultList::~DataResultList() { delete mQDataResultString; }

void DataResultList::Update(Message *msg) {
    mDataResultList.clear();
    String str(mQDataResultString->m_szContent);
    if (!str.empty() && str[0] == '[') {
        JsonConverter jc;
        JsonObject *jsonObj = jc.LoadFromString(str);
        MILO_ASSERT(jsonObj->GetType() == JsonObject::kType_Array, 0x3B);
        JsonArray *jsonArr = (JsonArray *)jsonObj;
        for (uint i = 0; i < jsonArr->GetSize(); i++) {
            JsonObject *tmpJsonObject = jc.GetElement(jsonArr, i);
            MILO_ASSERT(tmpJsonObject->GetType() == JsonObject::kType_Array, 0x45);
            JsonArray *tmpJsonArray = (JsonArray *)tmpJsonObject;
            MILO_ASSERT(tmpJsonArray->GetSize() == 4, 0x49);
            tmpJsonObject = jc.GetElement(tmpJsonArray, 0);
            MILO_ASSERT(tmpJsonObject->GetType() == JsonObject::kType_String, 0x4D);
            String jsonAsStr = tmpJsonObject->GetObjectAsString();
            tmpJsonObject = jc.GetElement(tmpJsonArray, 1);
            MILO_ASSERT(tmpJsonObject->GetType() == JsonObject::kType_String, 0x52);
            String jsonStr1 = tmpJsonObject->GetObjectAsString();
            int nNumFields = jsonStr1.length();
            tmpJsonObject = jc.GetElement(tmpJsonArray, 2);
            MILO_ASSERT(tmpJsonObject->GetType() == JsonObject::kType_Array, 0x58);
            JsonArray *jsonFieldNames = (JsonArray *)tmpJsonObject;
            MILO_ASSERT(jsonFieldNames->GetSize() == nNumFields, 0x5A);
            tmpJsonObject = jc.GetElement(tmpJsonArray, 3);
            MILO_ASSERT(tmpJsonObject->GetType() == JsonObject::kType_Array, 0x5E);
            int size = jsonFieldNames->GetSize();
            for (uint j = 0; j < size; j++) {
                tmpJsonObject = jc.GetElement(tmpJsonArray, j);
                MILO_ASSERT(tmpJsonObject->GetType() == JsonObject::kType_Array, 0x65);
                DataResult res;
                res.mUrl = jsonAsStr;
                for (uint k = 0; k < nNumFields; k++) {
                    DataNode ne0;
                    tmpJsonObject = jc.GetElement(tmpJsonArray, k);
                    switch (jsonAsStr[k]) {
                    case 'd':
                        MILO_ASSERT(tmpJsonObject->GetType() == JsonObject::kType_Int, 0x74);
                        JsonInt *jInt = (JsonInt *)tmpJsonObject;
                        ne0 = jInt->GetValue();
                        break;
                    case 'f':
                        MILO_ASSERT(tmpJsonObject->GetType() == JsonObject::kType_Double, 0x79);
                        JsonDouble *jFloat = (JsonDouble *)tmpJsonObject;
                        ne0 = (float)jFloat->GetValue();
                        break;
                    case 's':
                        MILO_ASSERT(tmpJsonObject->GetType() == JsonObject::kType_String, 0x7E);
                        JsonString *jStr = (JsonString *)tmpJsonObject;
                        ne0 = jStr->GetValue();
                        break;
                    default:
                        MILO_FAIL("Unsupported type!");
                        break;
                    }
                    tmpJsonObject = jc.GetElement(tmpJsonArray, k);
                    MILO_ASSERT(tmpJsonObject->GetType() == JsonObject::kType_String, 0x88);
                    String pairStr = tmpJsonObject->GetObjectAsString();
                    res.mDataMap.insert(std::make_pair(pairStr, ne0));
                }
                mDataResultList.push_back(res);
            }
        }
    }
    mUpdated = true;
}