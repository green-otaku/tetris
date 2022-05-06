#include "game mode.h"
#include <random>
#include <limits>
#pragma warning(disable: 4244)

void menu_text::setPos(sf::RenderWindow& window) {
    tplay.setPosition(107, 170);
    tplay.setCharacterSize(40);
    toptions.setPosition(72, 240);
    toptions.setCharacterSize(40);
    tscores.setPosition(85, 310);
    tscores.setCharacterSize(40);
    texit.setPosition(113, 380);
    texit.setCharacterSize(40);
    for (auto i = 0; i < 16; i++) {
        buttons[i].setScale(1.5, 1.5);
        buttons[i].setPosition(55 + (i % 4) * (1.5 * DIMENSIONS.x + 2 * BORDER), 170 + 70 * (i / 4));
    }
    updatePos(window);
    logo.setScale(0.4f, 0.2f);
    logo.setPosition(20, 20);
}

void menu_text::updatePos(sf::RenderWindow& window) {
    play_data.top = window.getPosition().y + 170 + 30;
    play_data.left = window.getPosition().x + 55 + 5;
    play_data.height = play_data.top + 1.5 * DIMENSIONS.x + 2 * BORDER + 2;
    play_data.width = play_data.left + 4 * 1.5 * (DIMENSIONS.x + 2 * BORDER);

    options_data.top = window.getPosition().y + 170 + 70 + 30;
    options_data.left = window.getPosition().x + 55 + 5;
    options_data.height = options_data.top + 1.5 * DIMENSIONS.x + 2 * BORDER + 2;
    options_data.width = options_data.left + 4 * 1.5 * (DIMENSIONS.x + 2 * BORDER);

    scores_data.top = window.getPosition().y + 170 + 70 * 2 + 30;
    scores_data.left = window.getPosition().x + 55 + 5;
    scores_data.height = scores_data.top + 1.5 * DIMENSIONS.x + 2 * BORDER + 2;
    scores_data.width = scores_data.left + 4 * 1.5 * (DIMENSIONS.x + 2 * BORDER);

    exit_data.top = window.getPosition().y + 170 + 70 * 3 + 30;
    exit_data.left = window.getPosition().x + 55 + 5;
    exit_data.height = exit_data.top + 1.5 * DIMENSIONS.x + 2 * BORDER + 2;
    exit_data.width = exit_data.left + 4 * 1.5 * (DIMENSIONS.x + 2 * BORDER);
}

void menu_text::setColour(const Theme& t) {
    tplay.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    toptions.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    tscores.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    texit.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    auto temp = { 1, 2, 5, 6 };
    for (auto i = 0; i < 4; i++) {
        button_textures[i].loadFromFile("colours.png", sf::IntRect(*(temp.begin() + i) * (DIMENSIONS.x + 2 * BORDER), 1, DIMENSIONS.x + 2 * BORDER, DIMENSIONS.y + 3 * BORDER));
    }
    for (auto i = 0; i < 16; i++) {
        buttons[i].setTexture(button_textures[imgs[i / 4]]);
    }
    logo.setTexture(logo_texture);
}

void menu_text::draw(sf::RenderWindow& window) {
    for (auto& i : buttons)
        window.draw(i);
    window.draw(logo);
    window.draw(tplay);
    window.draw(toptions);
    window.draw(tscores);
    window.draw(texit);
}

void play_text::setPos(sf::RenderWindow& window) {
    t40l.setPosition(75, 170);
    t40l.setCharacterSize(40);
    t2m.setPosition(65, 240);
    t2m.setCharacterSize(36);
    tun.setPosition(65, 310);
    tun.setCharacterSize(36);
    tback.setPosition(104, 380);
    tback.setCharacterSize(40);
    for (auto i = 0; i < 16; i++) {
        buttons[i].setScale(1.5, 1.5);
        buttons[i].setPosition(55 + (i % 4) * (1.5 * DIMENSIONS.x + 2 * BORDER), 170 + 70 * (i / 4));
    }
    updatePos(window);
}

void play_text::updatePos(sf::RenderWindow& window) {
    t40l_data.top = window.getPosition().y + 170 + 30;
    t40l_data.left = window.getPosition().x + 55 + 5;
    t40l_data.height = t40l_data.top + 1.5 * DIMENSIONS.x + 2 * BORDER + 2;
    t40l_data.width = t40l_data.left + 4 * 1.5 * (DIMENSIONS.x + 2 * BORDER);

    t2m_data.top = window.getPosition().y + 170 + 70 + 30;
    t2m_data.left = window.getPosition().x + 55 + 5;
    t2m_data.height = t2m_data.top + 1.5 * DIMENSIONS.x + 2 * BORDER + 2;
    t2m_data.width = t2m_data.left + 4 * 1.5 * (DIMENSIONS.x + 2 * BORDER);

    tun_data.top = window.getPosition().y + 170 + 70 * 2 + 30;
    tun_data.left = window.getPosition().x + 55 + 5;
    tun_data.height = tun_data.top + 1.5 * DIMENSIONS.x + 2 * BORDER + 2;
    tun_data.width = tun_data.left + 4 * 1.5 * (DIMENSIONS.x + 2 * BORDER);

    tback_data.top = window.getPosition().y + 170 + 70 * 3 + 30;
    tback_data.left = window.getPosition().x + 55 + 5;
    tback_data.height = tback_data.top + 1.5 * DIMENSIONS.x + 2 * BORDER + 2;
    tback_data.width = tback_data.left + 4 * 1.5 * (DIMENSIONS.x + 2 * BORDER);
}

void play_text::setColour(const Theme& t) {
    t40l.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    t2m.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    tun.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    tback.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    for (auto i = 0; i < 16; i++) {
        buttons[i].setTexture(button_textures[imgs[i / 4]]);
    }
}

void play_text::draw(sf::RenderWindow& window) {
    for (auto& i : buttons)
        window.draw(i);
    window.draw(t40l);
    window.draw(t2m);
    window.draw(tun);
    window.draw(tback);
}

void options_text::key_config_text::setPos(sf::RenderWindow& window) {

    const auto text_pos_x = 30;
    const auto shape_pos_x = 20;
    const auto shape_pos_y = 25;
    const auto shape_size_y = 50;

    action[Left].text.setPosition(text_pos_x, 30);
    action[Left].text.setCharacterSize(34);
    saction[Left].setPosition(shape_pos_x, shape_pos_y);
    saction[Left].setSize(sf::Vector2f(220, shape_size_y));
    saction[Left].setOutlineThickness(BORDER);

    action[Right].text.setPosition(text_pos_x + 240, 30);
    action[Right].text.setCharacterSize(34);
    saction[Right].setPosition(shape_pos_x + 240, shape_pos_y);
    saction[Right].setSize(sf::Vector2f(220, shape_size_y));
    saction[Right].setOutlineThickness(BORDER);

    auto it = action.begin();
    it++;
    it++;
    for (auto i = 1; i < action.size() - 1; i++) {
        auto& [key, value] = *it++;
        value.text.setPosition(text_pos_x, 30 + i * 70);
        value.text.setCharacterSize(34);
        saction[key].setPosition(shape_pos_x, shape_pos_y + i * 70);
        saction[key].setSize(sf::Vector2f(460, shape_size_y));
        saction[key].setOutlineThickness(BORDER);
    }

    back.text.setPosition(text_pos_x + 20, 660);
    back.text.setCharacterSize(34);
    sback.setPosition(shape_pos_x, shape_pos_y + 9 * 70);
    sback.setSize(sf::Vector2f(140, shape_size_y));
    sback.setOutlineThickness(BORDER);

    confirm.text.setPosition(text_pos_x + 150, 660);
    confirm.text.setCharacterSize(34);
    sconfirm.setPosition(shape_pos_x + 150, shape_pos_y + 9 * 70);
    sconfirm.setSize(sf::Vector2f(160, shape_size_y));
    sconfirm.setOutlineThickness(BORDER);

    save.text.setPosition(text_pos_x + 340, 660);
    save.text.setCharacterSize(34);
    ssave.setPosition(shape_pos_x + 320, shape_pos_y + 9 * 70);
    ssave.setSize(sf::Vector2f(140, shape_size_y));
    ssave.setOutlineThickness(BORDER);

    updatePos(window);
}

void options_text::key_config_text::updatePos(sf::RenderWindow& window) {
    auto it = action.begin();
    for (auto i = 0; i < action.size(); i++) {
        auto& [key, value] = *it++;
        value.area.top = window.getPosition().y + saction[key].getPosition().y + 30;
        value.area.left = window.getPosition().x + saction[key].getPosition().x + 5;
        value.area.height = value.area.top + saction[key].getSize().y + 5;
        value.area.width = value.area.left + saction[key].getSize().x + 5;
    }

    back.area.top = window.getPosition().y + sback.getPosition().y + 30;
    back.area.left = window.getPosition().x + sback.getPosition().x + 5;
    back.area.height = back.area.top + sback.getSize().y + 5;
    back.area.width = back.area.left + sback.getSize().x + 5;

    confirm.area.top = window.getPosition().y + sconfirm.getPosition().y + 30;
    confirm.area.left = window.getPosition().x + sconfirm.getPosition().x + 5;
    confirm.area.height = confirm.area.top + sconfirm.getSize().y + 5;
    confirm.area.width = confirm.area.left + sconfirm.getSize().x + 5;

    save.area.top = window.getPosition().y + ssave.getPosition().y + 30;
    save.area.left = window.getPosition().x + ssave.getPosition().x + 5;
    save.area.height = save.area.top + ssave.getSize().y + 5;
    save.area.width = save.area.left + ssave.getSize().x + 5;

    action[Left].text.setString("Left:  " + temp_settings[Left]);
    action[Right].text.setString("Right:  " + temp_settings[Right]);
    action[Instant_Down].text.setString("Instant down:    " + temp_settings[Instant_Down]);
    action[Instant_Place].text.setString("Instant place:    " + temp_settings[Instant_Place]);
    action[Rotate_Right].text.setString("Rotate right:    " + temp_settings[Rotate_Right]);
    action[Rotate_Left].text.setString("Rotate left:    " + temp_settings[Rotate_Left]);
    action[Rotate_180].text.setString("Rotate 180:    " + temp_settings[Rotate_180]);
    action[Hold].text.setString("Hold:    " + temp_settings[Hold]);
    action[Restart].text.setString("Restart:    " + temp_settings[Restart]);
    action[Forfeit].text.setString("Forfeit:    " + temp_settings[Forfeit]);
}

void options_text::key_config_text::draw(sf::RenderWindow& window) {
    for (auto const& [key, value] : action) {
        window.draw(saction[key]);
        window.draw(value.text);
    }
    window.draw(sback);
    window.draw(back.text);
    window.draw(ssave);
    window.draw(save.text);
    window.draw(sconfirm);
    window.draw(confirm.text);
}

void options_text::key_config_text::setColour(const Theme& t) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 3); // [0, 3] || [0, 4)

    int val = 0;
    
    Key_Action temp = Left;
    for (auto& [key, value] : action) {
        value.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
        val = distrib(gen);
        saction[key].setFillColor(button_colours[val]);
        saction[key].setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
        shape_colour_id.push_back({ saction[key], val });
    }

    val = distrib(gen);
    back.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    shape_colour_id.push_back({ sback, val });
    sback.setFillColor(button_colours[val]);
    sback.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);

    val = distrib(gen);
    save.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    shape_colour_id.push_back({ ssave, val });
    ssave.setFillColor(button_colours[val]);
    ssave.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);

    val = distrib(gen);
    confirm.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    shape_colour_id.push_back({ sconfirm, val });
    sconfirm.setFillColor(button_colours[val]);
    sconfirm.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
}

void options_text::key_config_text::init() {

    action[Left].text.setString("Left:  ");
    action[Right].text.setString("Right:  ");
    action[Instant_Down].text.setString("Instant down:    ");
    action[Instant_Place].text.setString("Instant place:    ");
    action[Rotate_Right].text.setString("Rotate right:    ");
    action[Rotate_Left].text.setString("Rotate left:    ");
    action[Rotate_180].text.setString("Rotate 180:    ");
    action[Hold].text.setString("Hold:    ");
    action[Restart].text.setString("Restart:    ");
    action[Forfeit].text.setString("Forfeit:    ");
    back.text.setString("BACK");
    save.text.setString("SAVE");
    confirm.text.setString("CONFIRM");

    for (auto& [key, value] : action) value.text.setFont(font);
    back.text.setFont(font);
    save.text.setFont(font);
    confirm.text.setFont(font);
    confirm.text.setFont(font);

    foptions.open("./config.txt", std::ios::in);
    if (!foptions.good()) throw std::exception("could not open config.txt");
    std::string entry;
    std::getline(foptions, entry); // first line - general options

    for (auto& [key, value] : action) {
        std::getline(foptions, entry, ';');
        value.value = findByValue(key_to_string, entry);
        temp_settings[key] = key_to_string[value.value];
    }

    foptions.close();

    for (auto& [key, value] : action)
        value.text.setString(value.text.getString() + " " + key_to_string[key_id[key]]);
}

void options_text::setPos(sf::RenderWindow& window) {

    const auto text_pos_x = 30;
    const auto shape_pos_x = 20;
    const auto shape_pos_y = 25;
    const auto shape_size_y = 50;


    gravity.text.setPosition(text_pos_x, 30);
    gravity.text.setCharacterSize(34);
    sgravity.setPosition(shape_pos_x, shape_pos_y);
    sgravity.setSize(sf::Vector2f(460, shape_size_y));
    sgravity.setOutlineThickness(BORDER);

    theme.text.setPosition(text_pos_x, 100);
    theme.text.setCharacterSize(34);
    stheme.setPosition(shape_pos_x, shape_pos_y + 1 * 70);
    stheme.setSize(sf::Vector2f(460, shape_size_y));
    stheme.setOutlineThickness(BORDER);

    left_right_power.text.setPosition(text_pos_x, 170);
    left_right_power.text.setCharacterSize(34);
    sleft_right_power.setPosition(shape_pos_x, shape_pos_y + 2 * 70);
    sleft_right_power.setSize(sf::Vector2f(460, shape_size_y));
    sleft_right_power.setOutlineThickness(BORDER);

    instant_down_power.text.setPosition(text_pos_x, 240);
    instant_down_power.text.setCharacterSize(34);
    sinstant_down_power.setPosition(shape_pos_x, shape_pos_y + 3 * 70);
    sinstant_down_power.setSize(sf::Vector2f(460, shape_size_y));
    sinstant_down_power.setOutlineThickness(BORDER);

    block_texture.text.setPosition(text_pos_x, 310);
    block_texture.text.setCharacterSize(34);
    sblock_texture.setPosition(shape_pos_x, shape_pos_y + 4 * 70);
    sblock_texture.setSize(sf::Vector2f(460, shape_size_y));
    sblock_texture.setOutlineThickness(BORDER);

    lock_delay.text.setPosition(text_pos_x, 380);
    lock_delay.text.setCharacterSize(34);
    slock_delay.setPosition(shape_pos_x, shape_pos_y + 5 * 70);
    slock_delay.setSize(sf::Vector2f(460, shape_size_y));
    slock_delay.setOutlineThickness(BORDER);

    background.text.setPosition(text_pos_x, 450);
    background.text.setCharacterSize(34);
    sbackground.setPosition(shape_pos_x, shape_pos_y + 6 * 70);
    sbackground.setSize(sf::Vector2f(460, shape_size_y));
    sbackground.setOutlineThickness(BORDER);

    randomiser.text.setPosition(text_pos_x, 520);
    randomiser.text.setCharacterSize(34);
    srandomiser.setPosition(shape_pos_x, shape_pos_y + 7 * 70);
    srandomiser.setSize(sf::Vector2f(460, shape_size_y));
    srandomiser.setOutlineThickness(BORDER);

    back.text.setPosition(text_pos_x + 20, 660);
    back.text.setCharacterSize(34);
    sback.setPosition(shape_pos_x, shape_pos_y + 9 * 70);
    sback.setSize(sf::Vector2f(140, shape_size_y));
    sback.setOutlineThickness(BORDER);

    save.text.setPosition(text_pos_x + 340, 660);
    save.text.setCharacterSize(34);
    ssave.setPosition(shape_pos_x + 320, shape_pos_y + 9 * 70);
    ssave.setSize(sf::Vector2f(140, shape_size_y));
    ssave.setOutlineThickness(BORDER);

    key_config.this_data.text.setPosition(text_pos_x, 590);
    key_config.this_data.text.setCharacterSize(34);
    skey_config.setPosition(shape_pos_x, shape_pos_y + 8 * 70);
    skey_config.setSize(sf::Vector2f(460, shape_size_y));
    skey_config.setOutlineThickness(BORDER);

    updatePos(window);
}

void options_text::updatePos(sf::RenderWindow& window) {
    
    // I know that this could be done much better, I know, but I will NOT rewrite this code, period.

    gravity.area.top = window.getPosition().y + sgravity.getPosition().y + 30;
    gravity.area.left = window.getPosition().x + sgravity.getPosition().x + 5;
    gravity.area.height = gravity.area.top + sgravity.getSize().y + 5;
    gravity.area.width = gravity.area.left + sgravity.getSize().x + 5;

    theme.area.top = window.getPosition().y + stheme.getPosition().y + 30;
    theme.area.left = window.getPosition().x + stheme.getPosition().x + 5;
    theme.area.height = theme.area.top + stheme.getSize().y + 5;
    theme.area.width = theme.area.left + stheme.getSize().x + 5;

    left_right_power.area.top = window.getPosition().y + sleft_right_power.getPosition().y + 30;
    left_right_power.area.left = window.getPosition().x + sleft_right_power.getPosition().x + 5;
    left_right_power.area.height = left_right_power.area.top + sleft_right_power.getSize().y + 5;
    left_right_power.area.width = left_right_power.area.left + sleft_right_power.getSize().x + 5;

    instant_down_power.area.top = window.getPosition().y + sinstant_down_power.getPosition().y + 30;
    instant_down_power.area.left = window.getPosition().x + sinstant_down_power.getPosition().x + 5;
    instant_down_power.area.height = instant_down_power.area.top + sinstant_down_power.getSize().y + 5;
    instant_down_power.area.width = instant_down_power.area.left + sinstant_down_power.getSize().x + 5;

    block_texture.area.top = window.getPosition().y + sblock_texture.getPosition().y + 30;
    block_texture.area.left = window.getPosition().x + sblock_texture.getPosition().x + 5;
    block_texture.area.height = block_texture.area.top + sblock_texture.getSize().y + 5;
    block_texture.area.width = block_texture.area.left + sblock_texture.getSize().x + 5;

    lock_delay.area.top = window.getPosition().y + slock_delay.getPosition().y + 30;
    lock_delay.area.left = window.getPosition().x + slock_delay.getPosition().x + 5;
    lock_delay.area.height = lock_delay.area.top + slock_delay.getSize().y + 5;
    lock_delay.area.width = lock_delay.area.left +slock_delay.getSize().x + 5;

    background.area.top = window.getPosition().y + sbackground.getPosition().y + 30;
    background.area.left = window.getPosition().x + sbackground.getPosition().x + 5;
    background.area.height = background.area.top + sbackground.getSize().y + 5;
    background.area.width = background.area.left + sbackground.getSize().x + 5;

    randomiser.area.top = window.getPosition().y + srandomiser.getPosition().y + 30;
    randomiser.area.left = window.getPosition().x + srandomiser.getPosition().x + 5;
    randomiser.area.height = randomiser.area.top + srandomiser.getSize().y + 5;
    randomiser.area.width = randomiser.area.left + srandomiser.getSize().x + 5;

    back.area.top = window.getPosition().y + sback.getPosition().y + 30;
    back.area.left = window.getPosition().x + sback.getPosition().x + 5;
    back.area.height = back.area.top + sback.getSize().y + 5;
    back.area.width = back.area.left + sback.getSize().x + 5;

    save.area.top = window.getPosition().y + ssave.getPosition().y + 30;
    save.area.left = window.getPosition().x + ssave.getPosition().x + 5;
    save.area.height = save.area.top +  ssave.getSize().y + 5;
    save.area.width = save.area.left + ssave.getSize().x + 5;

    key_config.this_data.area.top = window.getPosition().y + skey_config.getPosition().y + 30;
    key_config.this_data.area.left = window.getPosition().x + skey_config.getPosition().x + 5;
    key_config.this_data.area.height = key_config.this_data.area.top + skey_config.getSize().y + 5;
    key_config.this_data.area.width = key_config.this_data.area.left + skey_config.getSize().x + 5;

    randomiser.text.setString(std::string("Randomiser:   ") + temp_settings[oRandomiser]);
    background.text.setString(std::string("Background:   ") + temp_settings[oBackground]);
    block_texture.text.setString(std::string("Block texture:   ") + temp_settings[oBlock_Texture]);
    left_right_power.text.setString(std::string("Side move power:   ")  + (std::stoi(temp_settings[oLR_Power]) != 9 ? temp_settings[oLR_Power] : "MAX"));
    instant_down_power.text.setString("Instant down power:  " + (std::stoi(temp_settings[oID_Power]) == 23 ? "MAX" : temp_settings[oID_Power]));
    theme.text.setString(std::string("Theme:   ") + temp_settings[oTheme]);
    gravity.text.setString(std::string("Gravity:   ") + (My_Double::getFromString(temp_settings[oGravity]).integral == 5 and My_Double::getFromString(temp_settings[oGravity]).decimal > 0 ? "INFINITE" :
        (My_Double::getFromString(temp_settings[oGravity]).integral == 0 and My_Double::getFromString(temp_settings[oGravity]).decimal == 0) ? "0.00" : (
         std::to_string(My_Double::getFromString(temp_settings[oGravity]).integral) + "." +  (My_Double::getFromString(temp_settings[oGravity]).decimal < 10 ?
             "0" + std::to_string(My_Double::getFromString(temp_settings[oGravity]).decimal) : std::to_string(My_Double::getFromString(temp_settings[oGravity]).decimal)))));
    lock_delay.text.setString(std::string("Lock delay:   ") + (My_Double::getFromString(temp_settings[oLock_Delay]).integral == 0 and My_Double::getFromString(temp_settings[oLock_Delay]).decimal == 0 ?
        "0.00" : My_Double::getFromString(temp_settings[oLock_Delay]).integral == 5 and My_Double::getFromString(temp_settings[oLock_Delay]).decimal > 0 ? 
        "INFINITE" : (std::to_string(My_Double::getFromString(temp_settings[oLock_Delay]).integral) + "." +
        (My_Double::getFromString(temp_settings[oLock_Delay]).decimal < 10 ? "0" + std::to_string(My_Double::getFromString(temp_settings[oLock_Delay]).decimal) :
            std::to_string(My_Double::getFromString(temp_settings[oLock_Delay]).decimal)))));
    
}

void options_text::draw(sf::RenderWindow& window) {
    window.draw(sgravity);
    window.draw(gravity.text);
    window.draw(stheme);
    window.draw(theme.text);
    window.draw(sleft_right_power);
    window.draw(left_right_power.text);
    window.draw(sinstant_down_power);
    window.draw(instant_down_power.text);
    window.draw(sblock_texture);
    window.draw(block_texture.text);
    window.draw(slock_delay);
    window.draw(lock_delay.text);
    window.draw(sbackground);
    window.draw(background.text);
    window.draw(srandomiser);
    window.draw(randomiser.text);
    window.draw(sback);
    window.draw(back.text);
    window.draw(ssave);
    window.draw(save.text);
    window.draw(skey_config);
    window.draw(key_config.this_data.text);
}

void options_text::setColour(const Theme& t) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 3); // [0, 3] || [0, 4)

    int value = 0;

    gravity.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    value = distrib(gen);
    sgravity.setFillColor(button_colours[value]);
    shape_colour_id.push_back({ sgravity, value });
    sgravity.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    theme.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    value = distrib(gen);
    stheme.setFillColor(button_colours[value]);
    shape_colour_id.push_back({ stheme, value });
    stheme.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    left_right_power.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    value = distrib(gen);
    sleft_right_power.setFillColor(button_colours[value]);
    shape_colour_id.push_back({ sleft_right_power, value });
    sleft_right_power.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    instant_down_power.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    value = distrib(gen);
    sinstant_down_power.setFillColor(button_colours[value]);
    shape_colour_id.push_back({ sinstant_down_power, value });
    sinstant_down_power.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    block_texture.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    value = distrib(gen);
    sblock_texture.setFillColor(button_colours[value]);
    shape_colour_id.push_back({ sblock_texture, value });
    sblock_texture.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    lock_delay.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    value = distrib(gen);
    slock_delay.setFillColor(button_colours[value]);
    shape_colour_id.push_back({ slock_delay, value });
    slock_delay.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    background.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    value = distrib(gen);
    sbackground.setFillColor(button_colours[value]);
    shape_colour_id.push_back({ sbackground, value });
    sbackground.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    randomiser.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    value = distrib(gen);
    srandomiser.setFillColor(button_colours[value]);
    shape_colour_id.push_back({ srandomiser, value });
    srandomiser.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    back.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    value = distrib(gen);
    sback.setFillColor(button_colours[value]);
    shape_colour_id.push_back({ sback, value });
    sback.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    save.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    value = distrib(gen);
    ssave.setFillColor(button_colours[value]);
    shape_colour_id.push_back({ ssave, value });
    ssave.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    key_config.this_data.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    value = distrib(gen);
    skey_config.setFillColor(button_colours[value]);
    shape_colour_id.push_back({ skey_config, value });
    skey_config.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
}

void options_text::init() {
    gravity.text.setFont(font);
    theme.text.setFont(font);
    left_right_power.text.setFont(font);
    instant_down_power.text.setFont(font);
    block_texture.text.setFont(font);
    lock_delay.text.setFont(font);
    background.text.setFont(font);
    randomiser.text.setFont(font);
    back.text.setFont(font);
    save.text.setFont(font);
    key_config.this_data.text.setFont(font);

    gravity.text.setString("Gravity:   ");
    theme.text.setString("Theme:   ");
    left_right_power.text.setString("Side move power:   ");
    instant_down_power.text.setString("Instant down power:  ");
    block_texture.text.setString("Block texture:   ");
    lock_delay.text.setString("Lock delay:   ");
    background.text.setString("Background:   ");
    randomiser.text.setString("Randomiser:  ");
    back.text.setString("BACK");
    save.text.setString("SAVE");
    key_config.this_data.text.setString("Key config");

    foptions.open("./config.txt", std::ios::in);
    if (!foptions.good()) throw std::exception("could not open config.txt");
    std::string entry;

    std::getline(foptions, entry, ';');
    gravity.value = My_Double::getFromString(entry); // in seconds
    temp_settings[oGravity] = entry;
    std::getline(foptions, entry, ';');
    theme.value = entry;
    temp_settings[oTheme] = entry;
    std::getline(foptions, entry, ';');
    left_right_power.value = std::stoi(entry); // [1, 9] - 1 MIN - 9 MAX
    temp_settings[oLR_Power] = entry;
    std::getline(foptions, entry, ';');
    instant_down_power.value = std::stoi(entry); // [1, 23] - 1 MIN - 23 MAX
    temp_settings[oID_Power] = entry;
    std::getline(foptions, entry, ';');
    block_texture.value = std::stoi(entry); // 1 - flexible, 0 - fixed
    temp_settings[oBlock_Texture] = entry;
    std::getline(foptions, entry, ';');
    auto temp = My_Double::getFromString(entry);
    lock_delay.value = { temp.integral, 10 * temp.decimal };
    temp_settings[oLock_Delay] = options_text::My_Double::toString(lock_delay.value);
    std::getline(foptions, entry, ';');
    background.value = std::stoi(entry); // 1 - most mostowski, 0 - tetris
    temp_settings[oBackground] = entry;
    std::getline(foptions, entry, ';');
    randomiser.value = entry; // 7BAG, 14BAG, RANDOM
    temp_settings[oRandomiser] = entry;

    foptions.close();

    gravity.text.setString(gravity.text.getString() + 
        std::to_string(gravity.value.integral) + "." + 
        std::to_string(gravity.value.decimal));
    theme.text.setString(theme.text.getString() +
        theme.value);
    left_right_power.text.setString(left_right_power.text.getString() +
        std::to_string(left_right_power.value));
    instant_down_power.text.setString(instant_down_power.text.getString() +
        std::to_string(instant_down_power.value));
    block_texture.text.setString(block_texture.text.getString() +
        std::to_string(block_texture.value));
    lock_delay.text.setString(lock_delay.text.getString() +
        std::to_string(lock_delay.value.integral) + "." +
        std::to_string(lock_delay.value.decimal));
    background.text.setString(background.text.getString() +
        std::to_string(background.value));
    randomiser.text.setString(randomiser.text.getString() +
        randomiser.value);

}

void scores_text::setPos(sf::RenderWindow& window) {

    const auto text_pos_x = 30;
    const auto shape_pos_x = 20;
    const auto shape_pos_y = 25;
    const auto shape_size_y = 50;

    for (auto& e : buttons) e.text.setFont(font);

    buttons[0].text.setString("40 LINES SCORES");
    buttons[1].text.setString("2 MINUTES SCORES");
    buttons[2].text.setString("UNLIMITED SCORES");
    buttons[3].text.setString("BACK");

    for (auto i = 0; i < 3; i++) {
        buttons[i].text.setPosition(text_pos_x + 20, (100 + shape_pos_y + 5) + i * 70);
        buttons[i].text.setCharacterSize(34);
        buttons[i].shape.setPosition(shape_pos_x, shape_pos_y + 100 + i * 70);
        buttons[i].shape.setSize(sf::Vector2f(360, shape_size_y));
        buttons[i].shape.setOutlineThickness(BORDER);
    }

    buttons[0].text.setPosition(text_pos_x + 35, (100 + shape_pos_y + 5) + 0 * 70);
    buttons[1].text.setPosition(text_pos_x + 25, (100 + shape_pos_y + 5) + 1 * 70);
    buttons[2].text.setPosition(text_pos_x + 20, (100 + shape_pos_y + 5) + 2 * 70);

    buttons[3].text.setPosition(text_pos_x + 20, 660);
    buttons[3].text.setCharacterSize(34);
    buttons[3].shape.setPosition(shape_pos_x, shape_pos_y + 9 * 70);
    buttons[3].shape.setSize(sf::Vector2f(140, shape_size_y));
    buttons[3].shape.setOutlineThickness(BORDER);

    updatePos(window);
}

void scores_text::updatePos(sf::RenderWindow& window) {
#define i auto& e

    for (i : buttons) {
        e.area.top = window.getPosition().y + e.shape.getPosition().y + 30;
        e.area.left = window.getPosition().x + e.shape.getPosition().x + 5;
        e.area.height = e.area.top + e.shape.getSize().y + 5;
        e.area.width = e.area.left + e.shape.getSize().x + 5;
    }

#undef i
}

void scores_text::draw(sf::RenderWindow& window) {
    for (auto& i : buttons) {
        window.draw(i.shape);
        window.draw(i.text);
    }
}

void scores_text::setColour(const Theme& t) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> get(0, 3); // [0,4) || [0, 3]
    for (auto& i : buttons) {
        i.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
        i.shape.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
        int value = get(gen);
        i.shape.setFillColor(button_colours[value]);
        shape_colour_id.push_back({ i.shape, value });
    }
}

void SavePrompt::show(sf::RenderWindow& window) {
    window.draw(mainShape);
    window.draw(discardButton.shape);
    window.draw(discardButton.text);
    window.draw(saveButton.shape);
    window.draw(saveButton.text);
}

void SavePrompt::init(sf::RenderWindow& window) {

    discardButton.text.setFont(font);
    discardButton.text.setCharacterSize(34);
    discardButton.text.setString("DISCARD (" + std::to_string(static_cast<int>(discardTimer.getElapsedTime().asSeconds())) + ")");

    saveButton.text.setFont(font);
    saveButton.text.setCharacterSize(34);
    saveButton.text.setString("SAVE");
}

void SavePrompt::setPos(sf::RenderWindow& window) {
    mainShape.setPosition(40, 300);
    mainShape.setSize(sf::Vector2f(300, 160));
    mainShape.setOutlineThickness(BORDER);

    discardButton.shape.setPosition(60, 320);
    discardButton.shape.setSize(sf::Vector2f(260, 50));
    discardButton.shape.setOutlineThickness(BORDER);
    discardButton.text.setPosition(62, 322);

    saveButton.shape.setPosition(60, 390);
    saveButton.shape.setSize(sf::Vector2f(260, 50));
    saveButton.shape.setOutlineThickness(BORDER);
    saveButton.text.setPosition(62, 392);

}

void SavePrompt::updatePos(sf::RenderWindow& window) {
    discardButton.area.top = window.getPosition().y + discardButton.shape.getPosition().y + 30;
    discardButton.area.left = window.getPosition().x + discardButton.shape.getPosition().x + 5;
    discardButton.area.height = discardButton.area.top + discardButton.shape.getSize().y;
    discardButton.area.width = discardButton.area.left +discardButton.shape.getSize().x + 5;

    saveButton.area.top = window.getPosition().y + saveButton.shape.getPosition().y + 30;
    saveButton.area.left = window.getPosition().x + saveButton.shape.getPosition().x + 5;
    saveButton.area.height = saveButton.area.top + saveButton.shape.getSize().y;
    saveButton.area.width = saveButton.area.left + saveButton.shape.getSize().x + 5;
}

void SavePrompt::setColour(const Theme& t) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> get(0, 3); // [0, 4)

    mainShape.setFillColor(button_colours[get(gen)]);
    mainShape.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);

    int value = get(gen);
    discardButton.shape.setFillColor(button_colours[value]);
    discardButton.colour = value;
    discardButton.shape.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    discardButton.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    // copy-paste manoeuvre
    value = get(gen);
    saveButton.shape.setFillColor(button_colours[value]);
    saveButton.colour = value;
    saveButton.shape.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    saveButton.text.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
}

bool SavePrompt::operate(sf::RenderWindow& window, ScoreEntry entry) {
    sf::Event event;
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed)
            window.close();

        updatePos(window);
        auto mouse_pos = sf::Mouse::getPosition();

        if (mouseIn(discardButton.area, mouse_pos)) {
            discardButton.shape.setFillColor(button_colours[4]);
        }
        else discardButton.shape.setFillColor(button_colours[discardButton.colour]);
        
        if (mouseIn(saveButton.area, mouse_pos)) {
            saveButton.shape.setFillColor(button_colours[4]);
        }
        else saveButton.shape.setFillColor(button_colours[saveButton.colour]);

        if (event.type == sf::Event::MouseButtonPressed and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (mouseIn(discardButton.area, mouse_pos)) {
                return true;
            }
            else if (mouseIn(saveButton.area, mouse_pos)) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> get(0, 3);
                entry.colour = get(gen);
                entry.init(t);
                fscores.open("./scores.txt", std::ios::app);
                if (gm == GM_40_LINES) {
                    entry.mode = ScoreEntry::_40L;
                    scores40L.scores.push_back(entry);
                    fscores << entry;
                    fscores.close();
                    return true;
                }
                else if (gm == GM_2_MIN) {
                    entry.mode = ScoreEntry::_2M;
                    scores2M.scores.push_back(entry);
                    fscores << entry;
                    fscores.close();
                    return true;
                }
                else if (gm == GM_UNLIMITED) {
                    entry.mode = ScoreEntry::_UN;
                    scoresUN.scores.push_back(entry);
                    fscores << entry;
                    fscores.close();
                    return true;
                }
            }
        }
    }

    if (discardTimer.getElapsedTime().asSeconds() >= (10 + 1)) return true;
    return false;
}

void ScoreEntry::init(const Theme& t) {
    shape.setSize(sf::Vector2f(400, 80));
    shape.setPosition(30, 100);
    shape.setOutlineThickness(BORDER);
    shape.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);

    for (auto i = 0; i < separator.size(); i++) {
        separator[i].setSize(sf::Vector2f(BORDER, 70));
        separator[i].setPosition(30 + 120 * i, 100);
        separator[i].setOutlineThickness(BORDER);
        separator[i].setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    }
}

void ScoreEntry::draw(sf::RenderWindow& window) {
    if (colour != -1) {
        window.draw(shape);
        for (auto& i : separator) window.draw(i); 
        window.draw(pieceData.tpieces);
        window.draw(pieceData.tpieces_count);
        window.draw(pieceData.tpps);

        window.draw(lineData.tlines);
        window.draw(lineData.tlines_count);
        window.draw(lineData.tlines_goal);

        window.draw(scoreData.tscore);
        window.draw(scoreData.tscore_number);

        window.draw(timeData.tmilliseconds);
        window.draw(timeData.tseconds);
        window.draw(timeData.ttime);
    }
}

void ScoreModeMenu_t::load(sf::RenderWindow& window) {
    fscores.open("./scores.txt", std::ios::in);
    scores40L.scores.clear();
    scores2M.scores.clear();
    scoresUN.scores.clear();
    ScoreEntry entry;
    ScoreEntry::Mode_t lastInsertion;
    while (!fscores.eof()) {
        fscores >> entry;
        if (entry.mode == ScoreEntry::_40L) {
            scores40L.scores.push_back(entry);
            lastInsertion = ScoreEntry::_40L;
        }
        else if (entry.mode == ScoreEntry::_2M) {
            scores2M.scores.push_back(entry);
            lastInsertion = ScoreEntry::_2M;
        }
        else if (entry.mode == ScoreEntry::_UN) {
            scoresUN.scores.push_back(entry);
            lastInsertion = ScoreEntry::_UN;
        }
    }
    if (lastInsertion == ScoreEntry::_40L)
        scores40L.scores.pop_back();
    else if (lastInsertion == ScoreEntry::_2M)
        scores2M.scores.pop_back();
    else if (lastInsertion == ScoreEntry::_UN)
        scoresUN.scores.pop_back();

    for (auto& i : scoresModes) {
        if (i.scores.size()) {
            //std::cout << i.scores[2].scoreData.tscore_number.getString().toAnsiString() << ' ' << i.scores[2].timeData.tseconds.getString().toAnsiString() << '\n';
            i.viewRange.first = 0;
            i.viewRange.second = (i.scores.size() >= 5 ? 5 : i.scores.size()) - 1;
            for (auto k = 0; k < (i.scores.size() >= 5 ? 5 : i.scores.size()); k++)
                i.view[k] = i.scores[k];
        }
    }
    fscores.close();
}

void ScoreModeMenu_t::init(sf::RenderWindow& window, const Theme& t) {
    const auto text_pos_x = 30;
    const auto shape_pos_x = 20;
    const auto shape_pos_y = 25;
    const auto shape_size_y = 50;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> get(0, 3);

    modeSeparator.setPosition(0, 0);
    modeSeparator.setSize(sf::Vector2f(WINDOW_WIDTH, 80));
    modeSeparator.setFillColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    modeSeparator.setOutlineThickness(BORDER);
    modeSeparator.setOutlineColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
    mode.setCharacterSize(60);
    mode.setOrigin(mode.getLocalBounds().width / 2.f, mode.getLocalBounds().top / 2.f);
    mode.setPosition(modeSeparator.getSize().x / 2.f, 10);

    for (auto& s : view) {
        s.pieceData.tpps.setFont(font);
        s.pieceData.tpieces.setFont(font);
        s.pieceData.tpieces_count.setFont(font);
        s.timeData.tmilliseconds.setFont(font);
        s.timeData.tseconds.setFont(font);
        s.timeData.ttime.setFont(font);
        s.lineData.tlines.setFont(font);
        s.lineData.tlines_count.setFont(font);
        s.lineData.tlines_goal.setFont(font);
        s.scoreData.tscore.setFont(font);
        s.scoreData.tscore_number.setFont(font);
    }
    
    back.colour = get(gen);
    back.text.setFont(font);
    back.text.setString("BACK");
    back.text.setPosition(text_pos_x + 20, 660);
    back.text.setCharacterSize(34);
    back.shape.setPosition(shape_pos_x, shape_pos_y + 9 * 70);
    back.shape.setSize(sf::Vector2f(140, shape_size_y));
    back.shape.setOutlineThickness(BORDER);
    back.shape.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    back.shape.setFillColor(button_colours[back.colour]);

    remove.colour = get(gen);
    remove.text.setFont(font);
    remove.text.setString("REMOVE");
    remove.text.setPosition(text_pos_x + 317, 660);
    remove.text.setCharacterSize(34);
    remove.shape.setPosition(shape_pos_x + 320, shape_pos_y + 9 * 70);
    remove.shape.setSize(sf::Vector2f(140, shape_size_y));
    remove.shape.setOutlineThickness(BORDER);
    remove.shape.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
    remove.shape.setFillColor(button_colours[remove.colour]);

    for (auto i = 0; i < view.size(); i++) {
        auto& s = view[i].shape;
        auto& time = view[i].timeData;
        auto& score = view[i].scoreData;
        auto& piece = view[i].pieceData;
        auto& line = view[i].lineData;
        if (view[i].colour != -1) {
            for (auto j = 0; j < view[i].separator.size(); j++) {
                auto& p = view[i].separator[j];
                p.setSize(sf::Vector2f(BORDER, 80));
                p.setFillColor(t == Theme::Dark ? sf::Color::White : sf::Color::Black);
                p.setPosition(30 + 440 / (view[i].separator.size() + 1) * (j + 1), (i + 1) * 108 + 5);
            }
            s.setOutlineThickness(BORDER);
            s.setOutlineColor(t == Theme::Dark ? sf::Color::Black : sf::Color::White);
            s.setPosition(30, (i + 1) * 108);
            s.setSize(sf::Vector2f(440, 90));
            s.setFillColor(button_colours[view[i].colour]);
            score.tscore.setPosition(30, (i + 1) * 108);
            score.tscore_number.setPosition(30, (i + 1) * 108 + 40);
            score.tscore_number.setCharacterSize(40);
            time.ttime.setPosition(140, (i + 1) * 108);
            time.tseconds.setPosition(140, (i + 1) * 108 + 40);
            time.tmilliseconds.setPosition(140 + 30, (i + 1) * 108 + 40);
            piece.tpieces.setPosition(250, (i + 1) * 108);
            piece.tpieces_count.setPosition(250, (i + 1) * 108 + 40);
            piece.tpps.setPosition(250 + 30, (i + 1) * 108 + 40);
            line.tlines.setPosition(360, (i + 1) * 108);
            line.tlines_count.setPosition(360, (i + 1) * 108 + 40);
            line.tlines_goal.setPosition(360 + 30, (i + 1) * 108 + 40);
        }
    }

    updatePos(window);
}

void ScoreModeMenu_t::updatePos(sf::RenderWindow& window) {
    back.area.top = window.getPosition().y + back.shape.getPosition().y + 30;
    back.area.left = window.getPosition().x + back.shape.getPosition().x + 5;
    back.area.height = back.area.top + back.shape.getSize().y + 5;
    back.area.width = back.area.left + back.shape.getSize().x + 5;

    remove.area.top = window.getPosition().y + remove.shape.getPosition().y + 30;
    remove.area.left = window.getPosition().x + remove.shape.getPosition().x + 5;
    remove.area.height = remove.area.top + remove.shape.getSize().y + 5;
    remove.area.width = remove.area.left + remove.shape.getSize().x + 5;

}

void ScoreModeMenu_t::draw(sf::RenderWindow& window) {
    window.draw(modeSeparator);
    window.draw(mode);
    window.draw(back.shape);
    window.draw(back.text);
    window.draw(remove.shape);
    window.draw(remove.text);

    for (auto& i : view)
        i.draw(window);
}

void ScoreModeMenu_t::update(sf::RenderWindow& window) {

}

void ScoreModeMenu_t::operate(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        
        if (event.type == sf::Event::Closed)
            window.close();

        updatePos(window);
        auto mouse_pos = sf::Mouse::getPosition();

        if (mouseIn(back.area, mouse_pos)) {
            back.shape.setFillColor(button_colours[4]);
        }
        else back.shape.setFillColor(button_colours[back.colour]);

        if (scoreSelected and mouseIn(remove.area, mouse_pos)) {
            remove.shape.setFillColor(button_colours[4]);
        }
        else remove.shape.setFillColor(button_colours[remove.colour]);

        if (event.type == sf::Event::MouseButtonPressed and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (mouseIn(back.area, mouse_pos)) {
                action_clicked[Scores] = true;
                action_clicked[Scores_40L] = false;
                action_clicked[Scores_2M] = false;
                action_clicked[Scores_UN] = false;
                return void();
            }

            if (scoreSelected and mouseIn(remove.area, mouse_pos)) {

            }
        }

    }

    window.clear();
    window.draw(background);
    
    draw(window);

    window.display();

}

bool game(sf::RenderWindow& window, game_mode const& gm) {
    bool leave = false;
    restart_game = false;

    const float delta_time = key_clock.restart().asSeconds();
    current->setGhost();

    sf::Event event;
    while (window.pollEvent(event))
    {

        //if (event.type == sf::Event::Resized) {
        //    //window.setSize();
        //    view.setSize(window.getSize().x, window.getSize().y);
        //}

        if (event.type == sf::Event::Closed)
            window.close();


        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == toptions_menu.key_config.action[Left].value) {
                lock_change++;
                key_info[event.key.code].isPressed = true;
            }
            else if (event.key.code == toptions_menu.key_config.action[Right].value) {
                lock_change++;
                key_info[event.key.code].isPressed = true;
            }
            else if (event.key.code == toptions_menu.key_config.action[Rotate_Right].value) {
                lock_change++;
                current->rotate(90);
            }
            else if (event.key.code == toptions_menu.key_config.action[Rotate_180].value) {
                lock_change++;
                current->rotate(180);
            }
            else if (event.key.code == toptions_menu.key_config.action[Rotate_Left].value) {
                lock_change++;
                current->rotate(270);
            }
            else if (event.key.code == toptions_menu.key_config.action[Instant_Down].value) {
                gravity_clock.restart();
                lock_change++;
                current->instantMove(None, RightDown, false, &new_piece);
            }
            else if (event.key.code == toptions_menu.key_config.action[Instant_Place].value) {
                lock_change++;
                current->instantMove(None, RightDown, true, &new_piece);
            }
            else if (event.key.code == toptions_menu.key_config.action[Hold].value) {
                if (can_change) {
                    if (!temp) {
                        temp = current;
                        temp_sprites = emplaceTemp(temp);
                        temp->resetPosition();
                        current = next.front();
                        next.pop_front();
                        next.push_back(generatePiece(toptions_menu.randomiser.value, false));
                        current->emplace();
                    }
                    else {
                        auto t = temp;
                        temp = current;
                        current = t;
                        temp_sprites = emplaceTemp(temp);
                        temp->resetPosition();
                        current->emplace();
                    }
                    can_change = false;
                }
            }
            else if (event.key.code == toptions_menu.key_config.action[Restart].value) {
                restart_game = true;
            }
            else if (event.key.code == toptions_menu.key_config.action[Forfeit].value) {
                leave = true;
            }
        }

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == toptions_menu.key_config.action[Left].value or event.key.code == toptions_menu.key_config.action[Right].value)
                keyReleased(event);
        }
    }

    time_data.game_time = sf::milliseconds(time_data.clock.getElapsedTime().asMilliseconds());
    auto asSeconds = static_cast<int>(time_data.game_time.asSeconds());
    time_data.tseconds.setString(
        std::to_string(asSeconds / 60) + ":"
        + (asSeconds % 60 >= 10 ? "" : "0")
        + std::to_string(asSeconds % 60)
    );
    auto ms = time_data.game_time.asMilliseconds() % 1000;
    time_data.tmilliseconds.setString(":" + (ms < 10 ? "00" + std::to_string(ms) : 
        (ms < 100 ? "0" + std::to_string(ms) : std::to_string(ms))));
    time_data.update();
    auto piecesOverTime = piece_data.pieces / time_data.game_time.asSeconds() * 100;
    int piecesOverTimeDecimal = static_cast<int>(piecesOverTime) % 100;
    piece_data.tpps.setString(
        std::to_string(static_cast<int>(piecesOverTime) / 100)
        + "." + (piecesOverTimeDecimal < 10 ? "0" : "") + std::to_string(piecesOverTimeDecimal) + "/S"
    );
    piece_data.update();
    line_data.update();
    score_data.tscore_number.setString(std::to_string(score_data.score));

    for (auto& [key, value] : key_info) {
        if (value.isPressed) {
            value.duration += delta_time;
            if (key == toptions_menu.key_config.action[Left].value or key == toptions_menu.key_config.action[Right].value) {
                keySideMove(key, value, current);
            }
        }
    }

    if (checkIfDead(current) or restart_game or leave or checkGameMode(gm)) {
        if (!restart_game and !leave) {
            ScoreEntry entry;
            entry.pieceData = piece_data;
            entry.lineData = line_data;
            entry.scoreData = score_data;
            entry.timeData = time_data;
            bool leave = false;
            freeze(colours[current->this_colour]);
            prompt = new SavePrompt();
            prompt->setPos(window);
            prompt->init(window);
            prompt->setColour(t);

            sf::Clock waitClock;

            prompt->discardTimer.restart();
            while (waitClock.getElapsedTime().asSeconds() < (10 + 1)) {

                prompt->updatePos(window);

                window.clear(themeWindow(t));
                printBoard(window);
                printTemp(window, temp_sprites);
                printNext(window, next_sprites);
                printText(window);
                printBorders(window);
                prompt->discardButton.text.setString("DISCARD (" +
                    std::to_string(static_cast<int>(prompt->discardTimer.getElapsedTime().asSeconds()))
                    + ")");
                prompt->show(window);
                window.display();
                leave = prompt->operate(window, entry);
                if (leave) break;
            }
        }
        clearBoard();
        piece_data.reset();
        if (restart_game) time_data.reset();
        score_data.reset();
        line_data.reset();
        if (current) delete current;
        if (temp) {
            clearTemp(temp_sprites);
            delete temp;
            temp = nullptr;
        }
        next.clear();
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, 6);
        current = generatePiece(toptions_menu.randomiser.value, true);
        current->emplace();
        for (auto i = 0; i < 4; i++)
            next.push_back(generatePiece(toptions_menu.randomiser.value, false));
        next_sprites = emplaceNext(next);
        if (!restart_game) {
            for (auto& [key, value] : action_clicked)
                value = false;
            return false;
        }
        gravity_clock.restart();
    }

    if (new_piece) {
        checkIfClearLine(score_data.score);
        piece_data.pieces++;
        piece_data.tpieces_count.setString(std::to_string(piece_data.pieces));
        if(current) delete current;
        current = next.front();
        next.pop_front();
        next.push_back(generatePiece(toptions_menu.randomiser.value, false));
        current->emplace();
        new_piece = false;
        can_change = true;
        next_sprites = emplaceNext(next);
        auto time = piece_clock.getElapsedTime().asSeconds();
        if (time > 3.0) score_data.score += 10;
        else score_data.score += static_cast<int>(-13.33333 * time + 40);
        piece_clock.restart();
    }

    window.clear(themeWindow(t));
    //window.setView(view);

    printBoard(window);
    printTemp(window, temp_sprites);
    printNext(window, next_sprites);
    printText(window);
    printBorders(window);

    window.display();

    if (lock_change >= 2) lock_change = 2;
    if (toptions_menu.gravity.value.integral != 5 and toptions_menu.gravity.value.decimal != 5) {
        auto check = gravity_clock.getElapsedTime();
        bool yes = (toptions_menu.lock_delay.value.toDouble() > 5 ? false : true);
        if ((check.asSeconds() >= toptions_menu.gravity.value.toDouble() + lock_change * toptions_menu.lock_delay.value.toDouble() / 2) and yes) {
            current->move(None, RightDown, &new_piece);
            gravity_clock.restart();
            lock_change = 0;
        }
    }

    return true;
}

void main_menu(sf::RenderWindow& window) {

    sf::Event event;
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed)
            window.close();

        auto mouse_pos = sf::Mouse::getPosition();

        if (event.type == sf::Event::MouseMoved) {
            tmenu.updatePos(window);
            if (mouseIn(tmenu.play_data, mouse_pos))
                for (auto i = 0; i < 4; i++) tmenu.buttons[0 * 4 + i].setTexture(highlighted);
            else
                for (auto i = 0; i < 4; i++) tmenu.buttons[0 * 4 + i].setTexture(button_textures[0]);

            if (mouseIn(tmenu.options_data, mouse_pos))
                for (auto i = 0; i < 4; i++) tmenu.buttons[1 * 4 + i].setTexture(highlighted);
            else
                for (auto i = 0; i < 4; i++) tmenu.buttons[1 * 4 + i].setTexture(button_textures[1]);

            if (mouseIn(tmenu.scores_data, mouse_pos))
                for (auto i = 0; i < 4; i++) tmenu.buttons[2 * 4 + i].setTexture(highlighted);
            else
                for (auto i = 0; i < 4; i++) tmenu.buttons[2 * 4 + i].setTexture(button_textures[2]);

            if (mouseIn(tmenu.exit_data, mouse_pos))
                for (auto i = 0; i < 4; i++) tmenu.buttons[3 * 4 + i].setTexture(highlighted);
            else
                for (auto i = 0; i < 4; i++) tmenu.buttons[3 * 4 + i].setTexture(button_textures[3]);
        }
        
        if (event.type == sf::Event::MouseButtonPressed and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        
            if (mouseIn(tmenu.play_data, mouse_pos)) {
                action_clicked[Play] = true;
            }
            else if (mouseIn(tmenu.options_data, mouse_pos)) {
                action_clicked[Options] = true;
            }
            else if (mouseIn(tmenu.scores_data, mouse_pos)) {
                action_clicked[Scores] = true;
            }
            else if (mouseIn(tmenu.exit_data, mouse_pos)) {
                action_clicked[Exit] = true;
            }

        }

    }

    window.clear();
    window.draw(background);

    tmenu.draw(window);

    window.display();
}

void play_menu(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed)
            window.close();

        auto mouse_pos = sf::Mouse::getPosition();

        if (event.type == sf::Event::MouseMoved) {
            tplay_menu.updatePos(window);
            if (mouseIn(tplay_menu.t40l_data, mouse_pos))
                for (auto i = 0; i < 4; i++) tplay_menu.buttons[0 * 4 + i].setTexture(highlighted);
            else
                for (auto i = 0; i < 4; i++) tplay_menu.buttons[0 * 4 + i].setTexture(button_textures[0]);

            if (mouseIn(tplay_menu.t2m_data, mouse_pos))
                for (auto i = 0; i < 4; i++) tplay_menu.buttons[1 * 4 + i].setTexture(highlighted);
            else
                for (auto i = 0; i < 4; i++) tplay_menu.buttons[1 * 4 + i].setTexture(button_textures[1]);

            if (mouseIn(tplay_menu.tun_data, mouse_pos))
                for (auto i = 0; i < 4; i++) tplay_menu.buttons[2 * 4 + i].setTexture(highlighted);
            else
                for (auto i = 0; i < 4; i++) tplay_menu.buttons[2 * 4 + i].setTexture(button_textures[2]);

            if (mouseIn(tplay_menu.tback_data, mouse_pos))
                for (auto i = 0; i < 4; i++) tplay_menu.buttons[3 * 4 + i].setTexture(highlighted);
            else
                for (auto i = 0; i < 4; i++) tplay_menu.buttons[3 * 4 + i].setTexture(button_textures[3]);
        }

        if (event.type == sf::Event::MouseButtonPressed and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

            if (mouseIn(tplay_menu.t40l_data, mouse_pos)) {
                gm = GM_40_LINES;
                action_clicked[Play_40L] = true;
                action_clicked[Play] = false;
            }
            else if (mouseIn(tplay_menu.t2m_data, mouse_pos)) {
                gm = GM_2_MIN;
                action_clicked[Play_2M] = true;
                action_clicked[Play] = false;
            }
            else if (mouseIn(tplay_menu.tun_data, mouse_pos)) {
                gm = GM_UNLIMITED;
                action_clicked[Play_UN] = true;
                action_clicked[Play] = false;
            }
            else if (mouseIn(tplay_menu.tback_data, mouse_pos)) {
                for (auto& [key, value] : action_clicked)
                    value = false;
            }

        }

    }

    window.clear();
    window.draw(background);

    tplay_menu.draw(window);

    window.display();
}

void options(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed)
            window.close();

        toptions_menu.updatePos(window);
        auto mouse_pos = sf::Mouse::getPosition();

        if (mouseIn(toptions_menu.gravity.area, mouse_pos))
            toptions_menu.sgravity.setFillColor(button_colours[4]);
        else
            toptions_menu.sgravity.setFillColor(
                button_colours[findVal(toptions_menu.shape_colour_id, toptions_menu.sgravity)]);

        if (mouseIn(toptions_menu.theme.area, mouse_pos))
            toptions_menu.stheme.setFillColor(button_colours[4]);
        else
            toptions_menu.stheme.setFillColor(
                button_colours[findVal(toptions_menu.shape_colour_id, toptions_menu.stheme)]);

        if (mouseIn(toptions_menu.left_right_power.area, mouse_pos)) 
            toptions_menu.sleft_right_power.setFillColor(button_colours[4]);
        else
            toptions_menu.sleft_right_power.setFillColor(
                button_colours[findVal(toptions_menu.shape_colour_id, toptions_menu.sleft_right_power)]);

        if (mouseIn(toptions_menu.instant_down_power.area, mouse_pos))
            toptions_menu.sinstant_down_power.setFillColor(button_colours[4]);
        else
            toptions_menu.sinstant_down_power.setFillColor(
                button_colours[findVal(toptions_menu.shape_colour_id, toptions_menu.sinstant_down_power)]);

        if (mouseIn(toptions_menu.block_texture.area, mouse_pos)) 
            toptions_menu.sblock_texture.setFillColor(button_colours[4]);
        else
            toptions_menu.sblock_texture.setFillColor(
                button_colours[findVal(toptions_menu.shape_colour_id, toptions_menu.sblock_texture)]);

        if (mouseIn(toptions_menu.lock_delay.area, mouse_pos))
            toptions_menu.slock_delay.setFillColor(button_colours[4]);
        else
            toptions_menu.slock_delay.setFillColor(
                button_colours[findVal(toptions_menu.shape_colour_id, toptions_menu.slock_delay)]);

        if (mouseIn(toptions_menu.background.area, mouse_pos))
            toptions_menu.sbackground.setFillColor(button_colours[4]);
        else
            toptions_menu.sbackground.setFillColor(
                button_colours[findVal(toptions_menu.shape_colour_id, toptions_menu.sbackground)]);

        if (mouseIn(toptions_menu.randomiser.area, mouse_pos))
            toptions_menu.srandomiser.setFillColor(button_colours[4]);
        else
            toptions_menu.srandomiser.setFillColor(
                button_colours[findVal(toptions_menu.shape_colour_id, toptions_menu.srandomiser)]);

        if (mouseIn(toptions_menu.back.area, mouse_pos))
            toptions_menu.sback.setFillColor(button_colours[4]);
        else
            toptions_menu.sback.setFillColor(
                button_colours[findVal(toptions_menu.shape_colour_id, toptions_menu.sback)]);

        if (mouseIn(toptions_menu.save.area, mouse_pos))
            toptions_menu.ssave.setFillColor(button_colours[4]);
        else
            toptions_menu.ssave.setFillColor(
                button_colours[findVal(toptions_menu.shape_colour_id, toptions_menu.ssave)]);

        if (mouseIn(toptions_menu.key_config.this_data.area, mouse_pos))
            toptions_menu.skey_config.setFillColor(button_colours[4]);
        else
            toptions_menu.skey_config.setFillColor(
                button_colours[findVal(toptions_menu.shape_colour_id, toptions_menu.skey_config)]);

        if (event.type == sf::Event::MouseButtonPressed and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (mouseIn(toptions_menu.back.area, mouse_pos)) {
                action_clicked[Options] = false;
                toptions_menu.temp_settings[toptions_menu.oGravity] = options_text::My_Double::toString(toptions_menu.gravity.value);
                toptions_menu.temp_settings[toptions_menu.oTheme] = toptions_menu.theme.value;
                toptions_menu.temp_settings[toptions_menu.oID_Power] = std::to_string(toptions_menu.instant_down_power.value);
                toptions_menu.temp_settings[toptions_menu.oLR_Power] = std::to_string(toptions_menu.left_right_power.value);
                toptions_menu.temp_settings[toptions_menu.oBackground] = std::to_string(toptions_menu.background.value);
                toptions_menu.temp_settings[toptions_menu.oRandomiser] = toptions_menu.randomiser.value;
                toptions_menu.temp_settings[toptions_menu.oBlock_Texture] = std::to_string(toptions_menu.block_texture.value);
                toptions_menu.temp_settings[toptions_menu.oLock_Delay] = options_text::My_Double::toString(toptions_menu.lock_delay.value);
            }
            else if (mouseIn(toptions_menu.save.area, mouse_pos)) {
                if (toptions_menu.theme.value != toptions_menu.temp_settings[toptions_menu.oTheme]) {
                    toptions_menu.theme.value = toptions_menu.temp_settings[toptions_menu.oTheme];
                    t = (toptions_menu.theme.value == "DARK" ? Theme::Dark : Theme::Light);
                    updateTheme(t);
                }
                if (toptions_menu.instant_down_power.value != std::stoi(toptions_menu.temp_settings[toptions_menu.oID_Power]))
                    toptions_menu.instant_down_power.value = std::stoi(toptions_menu.temp_settings[toptions_menu.oID_Power]);
                if (toptions_menu.left_right_power.value != std::stoi(toptions_menu.temp_settings[toptions_menu.oLR_Power]))
                    toptions_menu.left_right_power.value = std::stoi(toptions_menu.temp_settings[toptions_menu.oLR_Power]);
                if (toptions_menu.block_texture.value != std::stoi(toptions_menu.temp_settings[toptions_menu.oBlock_Texture])) {
                    toptions_menu.block_texture.value = std::stoi(toptions_menu.temp_settings[toptions_menu.oBlock_Texture]);
                    TETRIS_COLOURS_MODE = (toptions_menu.block_texture.value ? TETRIS_COLOURS_FLEXIBLE : TETRIS_COLOURS_SET);
                }
                if (toptions_menu.background.value != std::stoi(toptions_menu.temp_settings[toptions_menu.oBackground])) {
                    toptions_menu.background.value = std::stoi(toptions_menu.temp_settings[toptions_menu.oBackground]);
                    initBackground(toptions_menu.background.value);
                }
                if (toptions_menu.randomiser.value != toptions_menu.temp_settings[toptions_menu.oRandomiser]) {
                    toptions_menu.randomiser.value = toptions_menu.temp_settings[toptions_menu.oRandomiser];
                }
                if (toptions_menu.gravity.value != options_text::My_Double::getFromString(toptions_menu.temp_settings[toptions_menu.oGravity])) {
                    toptions_menu.gravity.value = options_text::My_Double::getFromString(toptions_menu.temp_settings[toptions_menu.oGravity]);
                }
                if (toptions_menu.lock_delay.value != options_text::My_Double::getFromString(toptions_menu.temp_settings[toptions_menu.oLock_Delay])) {
                    toptions_menu.lock_delay.value = options_text::My_Double::getFromString(toptions_menu.temp_settings[toptions_menu.oLock_Delay]);
                }
                foptions.open("./config.txt", std::ios::out);
                foptions << toptions_menu.gravity.value.toDouble() << ';'
                    << toptions_menu.theme.value << ';'
                    << toptions_menu.left_right_power.value << ';'
                    << toptions_menu.instant_down_power.value << ';'
                    << toptions_menu.block_texture.value << ';'
                    << toptions_menu.lock_delay.value.toDouble() << ';'
                    << toptions_menu.background.value << ';'
                    << toptions_menu.randomiser.value << ";\n";
                for (auto const& [key, value] : toptions_menu.key_config.action) {
                    foptions << key_to_string[value.value] << ';';
                }
                foptions.close();
            }
            else if (mouseIn(toptions_menu.randomiser.area, mouse_pos)) {
                auto& this_option = toptions_menu.temp_settings[toptions_menu.oRandomiser];
                auto find = std::find_if(toptions_menu.randomiser_options.begin(), toptions_menu.randomiser_options.end(), [&](std::string const& s) {
                    return s == this_option;
                    });
                if (find != toptions_menu.randomiser_options.end() - 1) this_option = *(find + 1);
                else this_option = toptions_menu.randomiser_options.front();
            }
            else if (mouseIn(toptions_menu.background.area, mouse_pos)) {
                /*auto& this_option = toptions_menu.temp_settings[toptions_menu.oBackground];
                this_option == "1" ? this_option = "0" : this_option = "1";*/
            }
            else if (mouseIn(toptions_menu.block_texture.area, mouse_pos)) {
                /*auto& this_option = toptions_menu.temp_settings[toptions_menu.oBlock_Texture];
                this_option == "1" ? this_option = "0" : this_option = "1";*/
            }
            else if (mouseIn(toptions_menu.left_right_power.area, mouse_pos)) {
                auto& this_ = toptions_menu.temp_settings[toptions_menu.oLR_Power];
                auto this_option = std::stoi(toptions_menu.temp_settings[toptions_menu.oLR_Power]);
                this_option == 9 ? this_option = 0 : this_option += 1;
                this_ = std::to_string(this_option);
            }
            else if (mouseIn(toptions_menu.instant_down_power.area, mouse_pos)) {
                auto& this_ = toptions_menu.temp_settings[toptions_menu.oID_Power];
                auto this_option = std::stoi(toptions_menu.temp_settings[toptions_menu.oID_Power]);
                this_option == 23 ? this_option = 0 : this_option += 1;
                this_ = std::to_string(this_option);
            }
            else if (mouseIn(toptions_menu.theme.area, mouse_pos)) {
                /*auto& this_option = toptions_menu.temp_settings[toptions_menu.oTheme];
                this_option == "DARK" ? this_option = "LIGHT" : this_option = "DARK";*/
            }
            else if (mouseIn(toptions_menu.lock_delay.area, mouse_pos)) {
                auto [integral, decimal] = options_text::My_Double::getFromString(toptions_menu.temp_settings[toptions_menu.oLock_Delay]);
                const auto step = 10;
                decimal += step;
                if (decimal == 10 * step) {
                    integral++;
                    decimal = 0;
                }
                else if (integral == 5 and decimal > step) {
                    integral = 0;
                    decimal = 0;
                }
                toptions_menu.temp_settings[toptions_menu.oLock_Delay] = options_text::My_Double::toString(options_text::My_Double{ integral, decimal });
            }
            else if (mouseIn(toptions_menu.gravity.area, mouse_pos)) {
                auto [integral, decimal] = options_text::My_Double::getFromString(toptions_menu.temp_settings[toptions_menu.oGravity]);
                decimal -= 5;
                if (decimal < 0) {
                    integral--;
                    decimal = 100 - 5;
                }
                if (integral < 0) {
                    integral = 5;
                    decimal = 5;
                }
                toptions_menu.temp_settings[toptions_menu.oGravity] = options_text::My_Double::toString(options_text::My_Double{ integral, decimal });
            }
            else if (mouseIn(toptions_menu.key_config.this_data.area, mouse_pos)) {
                action_clicked[Options] = false;
                toptions_menu.temp_settings[toptions_menu.oGravity] = options_text::My_Double::toString(toptions_menu.gravity.value);
                toptions_menu.temp_settings[toptions_menu.oTheme] = toptions_menu.theme.value;
                toptions_menu.temp_settings[toptions_menu.oID_Power] = std::to_string(toptions_menu.instant_down_power.value);
                toptions_menu.temp_settings[toptions_menu.oLR_Power] = std::to_string(toptions_menu.left_right_power.value);
                toptions_menu.temp_settings[toptions_menu.oBackground] = std::to_string(toptions_menu.background.value);
                toptions_menu.temp_settings[toptions_menu.oRandomiser] = toptions_menu.randomiser.value;
                toptions_menu.temp_settings[toptions_menu.oBlock_Texture] = std::to_string(toptions_menu.block_texture.value);
                toptions_menu.temp_settings[toptions_menu.oLock_Delay] = options_text::My_Double::toString(toptions_menu.lock_delay.value);
                action_clicked[Key_Config] = true;
            }
        }

        else if (event.type == sf::Event::MouseButtonPressed and sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            if (mouseIn(toptions_menu.randomiser.area, mouse_pos)) {
                auto& this_option = toptions_menu.temp_settings[toptions_menu.oRandomiser];
                auto find = std::find_if(toptions_menu.randomiser_options.begin(), toptions_menu.randomiser_options.end(), [&](std::string const& s) {
                    return s == this_option;
                    });
                if (find != toptions_menu.randomiser_options.begin()) this_option = *(find - 1);
                else this_option = toptions_menu.randomiser_options.back();
            }
            else if (mouseIn(toptions_menu.background.area, mouse_pos)) {
                /*auto& this_option = toptions_menu.temp_settings[toptions_menu.oBackground];
                this_option == "1" ? this_option = "0" : this_option = "1";*/
            }
            else if (mouseIn(toptions_menu.block_texture.area, mouse_pos)) {
                /*auto& this_option = toptions_menu.temp_settings[toptions_menu.oBlock_Texture];
                this_option == "1" ? this_option = "0" : this_option = "1";*/
            }
            else if (mouseIn(toptions_menu.left_right_power.area, mouse_pos)) {
                auto& this_ = toptions_menu.temp_settings[toptions_menu.oLR_Power];
                auto this_option = std::stoi(toptions_menu.temp_settings[toptions_menu.oLR_Power]);
                this_option == 0 ? this_option = 9 : this_option -= 1;
                this_ = std::to_string(this_option);
            }
            else if (mouseIn(toptions_menu.instant_down_power.area, mouse_pos)) {
                auto& this_ = toptions_menu.temp_settings[toptions_menu.oID_Power];
                auto this_option = std::stoi(toptions_menu.temp_settings[toptions_menu.oID_Power]);
                this_option == 0 ? this_option = 23 : this_option -= 1;
                this_ = std::to_string(this_option);
            }
            else if (mouseIn(toptions_menu.theme.area, mouse_pos)) {
                /*auto& this_option = toptions_menu.temp_settings[toptions_menu.oTheme];
                this_option == "DARK" ? this_option = "LIGHT" : this_option = "DARK";*/
            }
            else if (mouseIn(toptions_menu.lock_delay.area, mouse_pos)) {
                auto [integral, decimal] = options_text::My_Double::getFromString(toptions_menu.temp_settings[toptions_menu.oLock_Delay]);
                const auto step = 10;
                decimal -= step;
                if (decimal < 0) {
                    integral--;
                    decimal = 9 * step;
                }
                if (integral < 0) {
                    integral = 5;
                    decimal = step;
                }
                toptions_menu.temp_settings[toptions_menu.oLock_Delay] = options_text::My_Double::toString(options_text::My_Double{ integral, decimal });
            }
            else if (mouseIn(toptions_menu.gravity.area, mouse_pos)) {
                auto [integral, decimal] = options_text::My_Double::getFromString(toptions_menu.temp_settings[toptions_menu.oGravity]);
                decimal += 5;
                if (decimal == 100) {
                    integral++;
                    decimal = 0;
                }
                if (integral >= 5 and decimal > 5) {
                    integral = 0;
                    decimal = 0;
                }
                toptions_menu.temp_settings[toptions_menu.oGravity] = options_text::My_Double::toString(options_text::My_Double{ integral, decimal });
            }
        }

    }

    window.clear();
    window.draw(background);

    toptions_menu.draw(window);

    window.display();
}

void key_options(sf::RenderWindow& window) {
    auto& [ckey, cvalue] = choosing_key;

    sf::Event event;
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed)
            window.close();

        toptions_menu.key_config.updatePos(window);
        auto mouse_pos = sf::Mouse::getPosition();

        if (!cvalue) {
            for (auto& [key, value] : toptions_menu.key_config.action) {
                if (mouseIn(value.area, mouse_pos)) {
                    toptions_menu.key_config.saction[key].setFillColor(button_colours[4]);
                }
                else toptions_menu.key_config.saction[key].setFillColor(button_colours[findVal(toptions_menu.key_config.shape_colour_id, toptions_menu.key_config.saction[key])]);
            }

            if (mouseIn(toptions_menu.key_config.back.area, mouse_pos)) {
                toptions_menu.key_config.sback.setFillColor(button_colours[4]);
            }
            else toptions_menu.key_config.sback.setFillColor(button_colours[findVal(toptions_menu.key_config.shape_colour_id, toptions_menu.key_config.sback)]);

            if (mouseIn(toptions_menu.key_config.save.area, mouse_pos)) {
                toptions_menu.key_config.ssave.setFillColor(button_colours[4]);
            }
            else toptions_menu.key_config.ssave.setFillColor(button_colours[findVal(toptions_menu.key_config.shape_colour_id, toptions_menu.key_config.ssave)]);

        }

        if (mouseIn(toptions_menu.key_config.confirm.area, mouse_pos)) {
            toptions_menu.key_config.sconfirm.setFillColor(button_colours[4]);
        }
        else toptions_menu.key_config.sconfirm.setFillColor(button_colours[findVal(toptions_menu.key_config.shape_colour_id, toptions_menu.key_config.sconfirm)]);

        if (event.type == sf::Event::MouseButtonPressed and sf::Mouse::isButtonPressed(sf::Mouse::Left) and !cvalue) {
            if (mouseIn(toptions_menu.key_config.back.area, mouse_pos)) {
                action_clicked[Key_Config] = false;
                action_clicked[Options] = false;
                for (auto& [key, value] : toptions_menu.key_config.action)
                    toptions_menu.key_config.temp_settings[key] = key_to_string[value.value];
            }
            else if (mouseIn(toptions_menu.key_config.save.area, mouse_pos)) {
                foptions.open("./config.txt", std::ios::in);
                std::string first;
                foptions >> first;
                foptions.close();
                foptions.open("./config.txt", std::ios::out);
                foptions << first << '\n';
                for (auto const& [key, value] : toptions_menu.key_config.action) {
                    foptions << key_to_string[value.value] << ';';
                }
                foptions.close();
            }
            else {
                for (auto& [key, value] : toptions_menu.key_config.action) {
                    if (mouseIn(value.area, mouse_pos)) {
                        cvalue = true;
                        ckey = key;
                    }
                }
            }
        }
        
        if (cvalue and event.type == sf::Event::KeyPressed) {
            toptions_menu.key_config.temp_settings[ckey] = key_to_string[event.key.code];
        }

        if (cvalue and event.type == sf::Event::MouseButtonPressed and sf::Mouse::isButtonPressed(sf::Mouse::Left) and mouseIn(toptions_menu.key_config.confirm.area, mouse_pos)) {
            toptions_menu.key_config.action[ckey].value = findByValue(key_to_string, toptions_menu.key_config.temp_settings[ckey]);
            cvalue = false;
        }
    }

    window.clear();
    window.draw(background);

    toptions_menu.key_config.draw(window);

    window.display();
}

void scores_menu(sf::RenderWindow& window) {

    sf::Event event;
    while (window.pollEvent(event)) {
        
        if (event.type == sf::Event::Closed)
            window.close();

        tscores_menu.updatePos(window);
        auto mouse_pos = sf::Mouse::getPosition();

        for (auto& e : tscores_menu.buttons) {
            if (mouseIn(e.area, mouse_pos)) {
                e.shape.setFillColor(button_colours[4]);
            }
            else
                e.shape.setFillColor(button_colours[findVal(tscores_menu.shape_colour_id, e.shape)]);
        }

        if (event.type == sf::Event::MouseButtonPressed and sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            ScoreModeMenu_t::load(window);
            if (mouseIn(tscores_menu.buttons[3].area, mouse_pos)) {
                action_clicked[Scores] = false;
            }
            else if (mouseIn(tscores_menu.buttons[0].area, mouse_pos)) {
                action_clicked[Scores] = false;
                action_clicked[Scores_40L] = true;
                scores40L.init(window, t);
            }
            else if (mouseIn(tscores_menu.buttons[1].area, mouse_pos)) {
                action_clicked[Scores] = false;
                action_clicked[Scores_2M] = true;
                scores2M.init(window, t);
            }
            else if (mouseIn(tscores_menu.buttons[2].area, mouse_pos)) {
                action_clicked[Scores] = false;
                action_clicked[Scores_UN] = true;
                scoresUN.init(window, t);
            }
        }
    }

    window.clear();
    window.draw(background);

    tscores_menu.draw(window);

    window.display();

}

bool checkGameMode(game_mode const& gm) {
    if (gm == GM_2_MIN and time_data.clock.getElapsedTime().asSeconds() >= 120) return true;
    else if (gm == GM_40_LINES and line_data.lines >= 40) return true;
    return false;
}

void freeze(sf::Texture& texture) {
    for (auto i = 0; i < WIDTH; i++) {
        for (auto j = 0; j < HEIGHT; j++) {
            if (board[j][i].getTexture() == &ghost) {
                board[j][i].setTexture(empty);
            }
            if (board[j][i].getTexture() != &empty and board[j][i].getTexture() != &blank) {
                board[j][i].setTexture(texture);
            }
        }
    }
}

bool mouseIn(const sf::IntRect& area, const sf::Vector2i& pos) {
    return (pos.x >= area.left and pos.x <= area.width and pos.y >= area.top and pos.y <= area.height);
}


template<class _Ty1, class _Ty2>
_Ty1 findByValue(const std::map<_Ty1, _Ty2>& map, const _Ty2& val) {
    for (auto const& [key, value] : map)
        if (value == val) return key;
    throw std::exception("no correct value found");
}

template<class _Ty1, class _Ty2>
_Ty2 findByKey(const std::map<_Ty1, _Ty2>& map, const _Ty1& val) {
    for (auto const& [key, value] : map)
        if (key == val) return value;
    throw std::exception("no correct key found");
}