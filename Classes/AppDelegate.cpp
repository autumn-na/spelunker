#include "AppDelegate.h"
#include "ClickerScene.h"
#include "SimpleAudioEngine.h"
#include "BlockSlideGameScene.h"
#include "MenuScene.h"
#include "Start.h"

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
    return 0; 
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		//glview = GLViewImpl::createWithFullScreen("cave");
		glview = GLViewImpl::createWithRect("cave", cocos2d::Rect(0, 0, 360, 640));
#else
        glview = GLViewImpl::create("cave");
#endif
        director->setOpenGLView(glview);
    }

    //director->setDisplayStats(true);

    director->setAnimationInterval(1.0 / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(720, 1280, ResolutionPolicy::SHOW_ALL);

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = StrartScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
