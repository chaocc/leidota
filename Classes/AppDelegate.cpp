#include "AppDelegate.h"
#include "GameScene.h"
#include "cocostudio/CCArmature.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");

        // �����windows�汾���ֶ����ô��ڴ�С������android�汾����Ҫ����
#ifdef WIN32
        glview->setFrameSize(1280, 800);
#endif
        director->setOpenGLView(glview);
    }

    // @_@ �ѵ�cocos2d 3.x�Ѿ�������Ӧ����ˣ���
    glview->setDesignResolutionSize(1280, 800, ResolutionPolicy::SHOW_ALL);

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = GameScene::create();

    /**
    *	�˴��Ȱ�һЩ��Դ���ؽ������Է�ֹ��һ��ʹ�õ�ʱ��Ῠ 
    */
    ArmatureDataManager::getInstance()->addArmatureFileInfo("skill/xuejingling_VFX.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("skill/YSG-VFX.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("projectileshape/Niu-wuqi.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("projectileshape/Pig-wuqi.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("projectileshape/Theif-wuqi.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("projectileshape/xuejingling-texiao.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("projectileshape/zhousi-wuqi.ExportJson");

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
