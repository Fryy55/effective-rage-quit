#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>

using namespace geode::prelude;


class $modify(HPauseLayer, PauseLayer) {
	$override void customSetup() {
		PauseLayer::customSetup();

		auto sprite = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
		auto exMark = CCSprite::createWithSpriteFrameName("exMark_001.png");
		exMark -> setScale(0.6f);
		exMark -> setPosition({7.f, 10.f});
		exMark -> setID("ex-mark-sprite"_spr);
		sprite -> setScale(0.6f);
		sprite -> setID("game-quit-button-sprite"_spr);

		sprite -> addChild(exMark);

		auto gameQuitButton = CCMenuItemSpriteExtra::create(
			sprite,
			this,
			menu_selector(HPauseLayer::onGameQuit)
		);
		gameQuitButton -> setID("game-quit-button"_spr);

		auto menu = this -> getChildByID("right-button-menu");
		menu -> addChild(gameQuitButton);
		menu -> updateLayout();

		return;
	}

	void onGameQuit(CCObject* sender) {
		if (Mod::get() -> getSettingValue<bool>("confirm") == true)
			createQuickPopup(
				"Quit Game",
				"Are you sure you want to <cr>quit</c>?",
				"Cancel", "Yes",
				300.f,
				[](auto, bool yes) {
					if (yes)
						utils::game::exit();
				}
			);
		else
			utils::game::exit();

		return;
	}
};