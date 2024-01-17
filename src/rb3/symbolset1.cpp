#include "stringtablelocks.hpp"
#include "symbol.hpp"

StringTableLockBegin lock1;

Symbol SymSetFeedbackState("set_feedback_state");
Symbol SymSetFileMerger("set_file_merger");
Symbol SymSetFilePath("set_file_path");
Symbol SymSetFillAudio("set_fill_audio");
Symbol SymSetFirstBeatOffset("set_first_beat_offset");

StringTableLockEnd unlock1;