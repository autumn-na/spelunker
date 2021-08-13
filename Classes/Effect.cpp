#include "Effect.h"
#include "ClickerScene.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
//Clicker Scene//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

Sequence* MonsterDamaged::create()
{
	ScaleTo* scale_x = ScaleTo::create(0.1f, 0.5f, 1.5f);
	ScaleTo* scale_y = ScaleTo::create(0.1f, 1.5f, 0.5f);
	ScaleTo* scale_normal = ScaleTo::create(0.1f, 1.0f, 1.0f);

	TintTo* tint_character = TintTo::create(0.175f, Color3B::GRAY);
	TintTo* tint_character_back = TintTo::create(0.175f, Color3B(255, 255, 255));

	Sequence* seq_gray = Sequence::create(tint_character, tint_character_back, NULL);
	Repeat* rept_gray = Repeat::create(seq_gray, 2);

	Sequence* seq_monster_damaged = Sequence::create(scale_x, scale_y, scale_normal, NULL);

	Spawn* spawn_effect = Spawn::create(rept_gray, seq_monster_damaged, NULL);

	Sequence* seq_effect = Sequence::create(spawn_effect, NULL);

	return seq_effect;
}

Sequence * PlayerDamagedByMonster::create(Sprite* spr_port)
{
	ScaleTo* scale_x = ScaleTo::create(0.1f, 0.5f, 1.5f);
	ScaleTo* scale_y = ScaleTo::create(0.1f, 1.5f, 0.5f);
	ScaleTo* scale_normal = ScaleTo::create(0.1f, 1.0f, 1.0f);

	Sequence* seq_monster_damaged = Sequence::create(scale_x, scale_y, scale_normal, NULL);

	TintTo* tint_character = TintTo::create(0.3f, Color3B::GRAY);
	TintTo* tint_character_back = TintTo::create(0.3f, Color3B(255, 255, 255));

	Sequence* seq_gray = Sequence::create(tint_character, tint_character_back, NULL);
	Repeat* rept_gray = Repeat::create(seq_gray, 3);

	Spawn* spawn_effect = Spawn::create(rept_gray, seq_monster_damaged, NULL);

	Sequence* seq_effect = Sequence::create(spawn_effect, NULL);
	//seq_effect->setTag(5);
	
	return seq_effect;
}

Sequence * PlayerLowHP::create()
{
	Show* show_blood = Show::create();
	Sequence* seq_show_blood = Sequence::create(show_blood, NULL);

	return seq_show_blood;
}

Sequence * PlayerHighHP::create()
{
	Hide* hide_blood = Hide::create();
	Sequence* seq_hide_blood = Sequence::create(hide_blood, NULL);

	return seq_hide_blood;
}

Sequence * PlayerDamagedEffect::create()
{
	FadeTo* fadein_layer = FadeTo::create(0.2f, 170);
	FadeTo* fadeout_layer = FadeTo::create(0.2f, 0);

	Sequence* seq_fade = Sequence::create(fadein_layer, fadeout_layer, NULL);

	return seq_fade;
}

Sequence * DamagedPortrait::create()
{
	MoveBy* move_port = MoveBy::create(0.05f, Vec2(-40, 0));
	Sequence* seq_move_port = Sequence::create(move_port, move_port->reverse(), move_port->reverse(), move_port, NULL);
	Repeat* rept_move_port = Repeat::create(seq_move_port, 1);

	TintTo* tint_port = TintTo::create(0.15f, Color3B::RED);
	TintTo* tint_port_back = TintTo::create(0.15f, Color3B(255, 255, 255));

	Sequence* seq_red = Sequence::create(tint_port, tint_port_back, NULL);
	Repeat* rept_red = Repeat::create(seq_red, 3);

	Spawn* spawn_damaged_port = Spawn::create(rept_move_port, rept_red, NULL);

	Sequence* seq_effect = Sequence::create(spawn_damaged_port, NULL);

	return seq_effect;
}

Sequence * DamagedHPBar::create()
{
	MoveBy* move_bar = MoveBy::create(0.05f, Vec2(-40, 0));
	Sequence* seq_move_bar = Sequence::create(move_bar, move_bar->reverse(), move_bar->reverse(), move_bar, NULL);

	TintTo* tint_bar_red = TintTo::create(0.25f, Color3B::RED);
	TintTo* tint_bar_back = TintTo::create(0.25f, Color3B(255, 255, 255));
	Sequence* seq_tint_bar = Sequence::create(tint_bar_red, tint_bar_back, NULL);
	Repeat* rept_tint_bar = Repeat::create(seq_tint_bar, 2);


	Spawn* spawn_damaged_bar = Spawn::create(rept_tint_bar, seq_move_bar, NULL);

	Sequence* seq_damaged_bar = Sequence::create(spawn_damaged_bar, NULL);

	return seq_damaged_bar;
}

Sequence * SkillGaugeUp::create()
{
	ScaleTo* scale_gauge = ScaleTo::create(0.2f, 1.2f);
	ScaleTo* scale_gauge_back = ScaleTo::create(0.2f,1.0f);

	Sequence* seq_effect = Sequence::create(scale_gauge, scale_gauge_back, NULL);

	return seq_effect;
}


Sequence * ArrowFadeIn::create()
{
	FadeOut* fade_out_arrow = FadeOut::create(0.1f);
	ScaleTo* scale_arrow = ScaleTo::create(0.25f, 0.5f);
	FadeIn* fade_in_arrow = FadeIn::create(0.0f);
	ScaleTo* sclae = ScaleTo::create(0.0f, 0.8f);

	Spawn* spawn_fadenbig = Spawn::create(fade_out_arrow, scale_arrow, NULL);

	Sequence* seq_arrow_fade_in = Sequence::create(spawn_fadenbig, sclae, fade_in_arrow, NULL);

	return seq_arrow_fade_in;
}

Sequence * ArrowFadeOut::create()
{
	FadeOut* fade_out_arrow = FadeOut::create(0.3f);
	ScaleTo* scale_arrow = ScaleTo::create(0.3f, 1.5f);
	FadeIn* fade_in_arrow = FadeIn::create(0.0f);
	ScaleTo* sclae = ScaleTo::create(0.0f, 0.8f);

	Spawn* spawn_fadensmall = Spawn::create(fade_out_arrow, scale_arrow, NULL);

	Sequence* seq_arrow_fade_out = Sequence::create(spawn_fadensmall, sclae, fade_in_arrow, NULL);

	return seq_arrow_fade_out;
}

/////////////////////////////////////////////////////////////////////////////////////////////////
//여기까지 Clicker Scene/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////

