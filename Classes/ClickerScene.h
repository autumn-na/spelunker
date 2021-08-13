#pragma once

#include "SkillManagement.h"
#include "HeroManagement.h"
#include "MonsterManagement.h"
#include "EquipmentManagement.h"
#include <time.h>
#include "Effect.h"
#include "ui/CocosGUI.h"

using namespace ui;

class ClickerScene : public Layer
{
public:
	static cocos2d::Scene* createScene();

	//GameStatus
	bool isGamePaused = false;
	bool isDebuging = false;

	//버튼 상태

	enum BUTTONSTATE
	{
		NORMAL,
		LOCKED,
		SKILL
	};
	
	bool isHeroEternalLife = false;
	bool isMonsterStunned = false;
	bool isTutorial = false;

	//Layers
	Layer* pause_layer;
	LayerColor* layer_skill_back;
	LayerColor* layer_skill;
	LayerColor* layer_tutorial;

	int button_state = BUTTONSTATE::NORMAL;

	//화살표 스프라이트 관련
	Sprite* spr_arrow_panel;
	Sprite* spr_arrow_default;
	Sprite* spr_arrow[4];
	Sprite* spr_arrow_sel;
	Sprite* spr_arrow_warning;
	Rect rect_arrow[4];

	//화살표 위치, 회전(초기화)
	Vec2 vec2_arrow[4] = { Vec2(272, 398), Vec2(272, 222), Vec2(448, 398), Vec2(448, 222) };
	int rotate_arrow[4] = { 270, 180, 0, 90 };

	//랜덤으로 생성하는 화살표 위치
	int arrow_direction_1;
	int arrow_direction_2;

	//세팅된 화살표의 갯수
	int arrow_num;

	//화살표가 터치할수 있는 상황인가
	int arrow_type[4];

	//일시정지 애니메이션
	Sprite* openAni;

	//화살표 위치
	enum ArrowDirection
	{
		LEFT_UP,
		LEFT_DOWN,
		RIGHT_UP,
		RIGHT_DOWN,
		NONE = 99
	};

	//화살표 종류
	enum ArrowType
	{
		DEFAULT,
		SET,
		WARNING
	};

	//몬스터 번호(임시)
	int monster_num;

	//플레이어가 터치한 좌표
	Vec2 touch_location;
	
	//터치 시
	Sprite* spr_hit_hero;
	Sprite* spr_hit_monster;
	Sprite* spr_damage_hero[10];

	Sprite* spr_skill_gauge_on;

	//플레이어 체력 표시(임시)
	Label* lab_hero_hp;

	//몬스터 체력 표시(임시)
	Label* lab_monster_hp;

	//플레이어 체력바
	Sprite* spr_hero_hp_bar_back;
	Sprite* spr_hero_hp_bar;

	//몬스터 체력바
	Sprite* spr_monster_hp_bar_back;
	Sprite* spr_monster_hp_bar;
	
	//프로그레스 타이머
	ProgressTimer* ptimer_hero_hp;
	ProgressTimer* ptimer_monster_hp;

	//체력 %
	float hero_hp_percent;
	float monster_hp_percent = 100.0f;

	enum Color
	{
		RED,
		ORANGE,
		YELLOW,
		GREEN,
		SKYBLUE,
		BLUE,
		PURPLE
	};

	//몬스터, 캐릭터 스프라이트
	//Sprite* spr_hero;
	Sprite* spr_monster;

	//캐릭터 초상화 스프라이트
	Sprite* spr_hero_portrait_back;
	Sprite* spr_hero_portrait_default;
	Sprite* spr_hero_portrait_damaged;
	Sprite* spr_hero_portrait_fever;

	//스킬 사용시 이미지들
	Sprite* spr_skill_use_panel;
	Sprite* spr_use_skill_icon[4];

	Sprite* spr_skill_frame;
	Sprite* spr_skill_icon[4];
	Sprite* spr_icon_frame[4];

	Sprite* spr_use_skill;

	//스킬 버튼들
	MenuItemSprite* menui_use_skill[4];

	//스킬 메뉴
	MenuItemImage* menui_skill;
	Menu* menu_skill;
	
	//백그라운드 이미지
	Sprite* spr_background;

	//알림 박스
	Sprite* spr_warning;
	Sprite* spr_shield;
	Sprite* spr_skill_not_enabled;

	Vec2 shield_position;

	//자물쇠 관련
	Sprite* spr_chain;
	Sprite* spr_lock;

	//초상화
	Sprite* spr_hero_portrait;
	Sprite* spr_monster_portrait;

	Label* lab_monster_name;

	//스킬 게이지 스프라이트
	Sprite* spr_skill_gauge;
	Sprite* spr_skill_gauge_back;

	//스킬 게이지 프로그레스 바
	ProgressTimer* ptimer_skill_gauge;
	ProgressTimer* ptimer_skill_effect;

	enum ZOrder
	{
		BACKGROUND,
		OBJECT,
		UI,
		NOTIFICATION
	};
	
	//액션들
	Place* place_monster_base;

	MoveBy* move_monster_back;
	MoveBy* move_monster_front;

	EaseBackIn* ease_monster_back;
	EaseBackIn* ease_monster_front;
	
	MoveBy* move_monster_back_critical;
	MoveBy* move_monster_front_critical;

	EaseBackIn* ease_monster_back_critical;
	EaseBackIn* ease_monster_front_critical;

	Sequence* seq_monster_attack;
	Sequence* seq_monster_critical_attack;

	DelayTime* lock_to_normal_delay;

	MoveBy* move_hero_dodge;

	Sequence* seq_hero_dodge;

	ScaleBy* scale_warning_big;
	ScaleBy* scale_warning_small;
	RepeatForever* seq_scale_warning;

	MoveBy* move_shield;
	FadeOut* fade_shield;
	FadeIn* fadein_shield;
	Hide* hide_shield;
	Place* place_shield;
	Sequence*  seq_shield;

	Sprite* spr_game_over;
	Sprite* spr_game_over_back;

	//피
	Sprite* spr_red;
	Sprite* spr_blood;

	Sequence* seq_arrow_touch;

	Sequence* seq_change;
	//이펙트
	Sequence* monster_damaged;
	Sequence* player_damaged_by_monster;
	Sequence* player_low_hp;
	Sequence* player_high_hp;
	Sequence* player_damaged_effect;
	Sequence* arrow_fade_big;
	Sequence* arrow_fade_small;
	Sequence* portrait_tint_red;
	Sequence* damaged_bar;
	Sequence* skill_gauge_up;

	enum EFFECTTAG
	{
		PORTRAIT_TINT_RED,
		DAMAGED_BAR
	};

	enum ActionTag
	{
		MOVEMONSTER,
		ATTACKMONSTER,
		CRITICALMONSTER
	};

	//빨간버튼 클릭한 터치 아이디;
	int warning_touch_id;
	
	//빨간버튼 방향
	int warning_arrow_direciton;

	//빨간버튼 클릭한 터치 위치
	Vec2 warning_touch_location;

	bool isWarningArrowAlive = false;

	bool isSkillEnable = false;

	//키보드 이벤트 리스너
	EventListenerKeyboard* lis_key_debug;

	//일시정지 메뉴
	Sprite* spr_pause_popup;

	Sprite* spr_pause;
	MenuItemSprite* menui_pause;
	Menu* menu_clicker;

	Sprite* spr_back_to_home;
	Sprite* spr_back_to_game;
	Sprite* spr_background_sound_on;
	Sprite* spr_background_sound_off;
	Sprite* spr_effect_sound_on;
	Sprite* spr_effect_sound_off;
	Sprite* spr_close;
	Sprite* spr_close_skill;
	Sprite* spr_skill_panel;

	MenuItemSprite* menui_back_to_home;
	MenuItemSprite* menui_back_to_game;
	MenuItemSprite* menui_background_sound_on;
	MenuItemSprite* menui_background_sound_off;
	MenuItemSprite* menui_effect_sound_on;
	MenuItemSprite* menui_effect_sound_off;
	MenuItemSprite* menui_close;
	MenuItemSprite* menui_close_skill;

	MenuItemToggle* menui_background_sound;
	MenuItemToggle* menui_effect_sound;

	Menu* menu_pause;
	Menu* menu_close_skill;

	Sprite* spr_skill_back;
	Sprite* spr_skill_back_sel;
	MenuItemSprite* menui_skill_back;
	Menu* menu_skill_back;

	Sprite* spr_boss_portrait;

	Sprite* spr_tutorial_npc;
	Sprite* spr_conversation_panel;

	Label* lab_tutorial;

	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	//초기화
	virtual bool init();
	void initLayer();	
	void initSprite();
	void initLabel();
	void initProgressBar();
	void initMenu();
	void initAction();
	void initHeroData();
	void initListener();
	void initPopup();
	void initEffect();
	void initSkillScrollView();

	//업데이트
	virtual void update(float dt);

	void startTutorial();
	void endTutorial();

	//버튼 상태 변경
	void changeButtonState(int state);

	//히어로, 몬스터 체력 표시
	void updateLabel();

	//화살표 세팅 관련
	void setDirection(int arrow_num); //화살표 위치 랜덤으로 정함
	void setArrow(); //정해진 화살표 위치에 따라 화살표를 set함
	void setWarningArrow(); //위험 화살표 세팅
	void setWarningValueToDefaultValue(); //위험 값을 원래 값으로 바꿈
	void setWarningArrowToDefault(); //위험 화살표를 원래 화살표로 바꿈

	//세팅된 화살표를 전부 터치하였는가?
	bool checkAllArrowIsDefault();

	//터치 관련
	virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
	virtual void onTouchesMoved(const std::vector<Touch*>& touches, Event *unused_event);
	virtual void onTouchesEnded(const std::vector<Touch*>& touches, Event *unused_event);

	//키보드 체크
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	//디버그용, 키보드로 게임 진행
	void checkKeyboardForDebug();

	//몬스터 생성
	void createMonster();

	//전투 관련
	bool criticalGamble(int _percent);
	void monsterAttack(float dt);
	void heroAttack(int arrow_num);
	void giveDamageTo(int type, float damage, bool isCritical);
	void noticeCondition(int type, int condition);

	enum TargetType
	{
		HERO,
		MONSTER
	};

	enum ConditionType
	{
		STUNNED,
		BURNNED
	};

	//몬스터가 크리티컬 공격을 할 때 회피했는가?
	bool checkIsPlayerDodged();

	//체력 체크(임시)
	void checkHp();

	//프로그레스 바 체크
	void checkPTimer();

	//이겼을때, 졌을때 일어나는 상황
	void clickerWin();
	void clickerLose();
	
	void changeScene(int _type);

	enum SceneType
	{
		BLOCKSLIDE,
		GAMEOVER,
		MAIN,
		CLICKER
	};

	//스킬 사용
	void useSkill(int num);

	//스킬 사용 불가 알림
	void noticeSkillNotEnabled();

	//모든 화살표 끔
	void offAllArrow();
	CREATE_FUNC(ClickerScene);

	//자물쇠 키고 끔
	void setLockVisible(int num);

	//스킬 게이지 증가
	void plusSkillGauge(int num);

	//스킬 게이지 프레임마다 체크, 0~99 스킬버튼 비활성화, 100 스킬버튼 활성화
	void checkSkillGauge();

	//체력 낮은가
	bool isPlayerHPLow();

	void changeSetArrowToDefault(int num);

	void setHeroData();

	//스킬들
	enum SkillName
	{
		RUINFIRE,
		RUINEYE,
		WAILGUST,
		ETERNALLIFE
	};

	void ruinFire();
	void ruinEye();
	void wailGust();
	void eternalLife();

	void stunTarget(int type, int sec);
	void burnTarget(int type);

	Sprite* runAnimation(const char* _path, const Vec2& position);

	//콜백들
	void pauseCallback(Ref* pSender);
	void returnGameCallback(Ref* pSender);
	void goToMainCallback(Ref* pSender);
	void toggleBackgroundCallback(Ref* pSender);
	void toggleEffectCallback(Ref* pSender);
	void changeButtonStateToSkillCallback(Ref* pSender);
	void closeSkillLayerCallback(Ref* pSender);
	void useSkillCallback(int num);
	void menuSceneCallBack();
	void endingSceneCallBack();
};
