#include <jni.h>
#include <dlfcn.h>
#include <Substrate.h>

class BlockSource;
class FurnaceBlockEntity{
public:
int getTickCount() const;
bool isSlotEmpty(int);
bool isLit();
void tick(BlockSource&);
void burn();
void resetBurnProgress(); 
void setTickCount(int);
};
void (*_hook)(FurnaceBlockEntity*,BlockSource&);
void hook(FurnaceBlockEntity* p,BlockSource& source){
_hook(p,source);
if(p->isLit()){
if(!p->isSlotEmpty(0)){
if(p->getTickCount()<200) p->setTickCount(p->getTickCount()+20);
else if(p->getTickCount()>=200){
p->burn();
p->resetBurnProgress();
}
}
else p->resetBurnProgress();
}
};

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved) {
MSHookFunction((void*)&FurnaceBlockEntity::tick,(void*)&hook,(void**)&_hook);
return JNI_VERSION_1_2;
}
