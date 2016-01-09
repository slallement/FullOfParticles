#include "OptionMenu.h"

OptionMenu::OptionMenu(sf::RenderWindow & win):
 Menu(win)
{
    sf::Text t = sf::Text("Resolution",*FontManager::getFont("ressources/Symtext.ttf"),32);
    option.resize(1);

    float pos_offset = 100.f;

    centerTextOnxAxis(t, pos_offset);
    option[0].txt = t;
    option[0].f = static_cast<void (Menu::*)()>(&OptionMenu::changeResolution);
    pos_offset += 40.f;

    // resolution modes
    offset_opt_resolution = 1;
    std::vector<sf::VideoMode> Modes = sf::VideoMode::getFullscreenModes();
    t.setCharacterSize(16);
    for (unsigned i=0; i<Modes.size(); i++){
        if(Modes[i].bitsPerPixel < 32)
            continue;
        t.setString( ttos(Modes[i].width) + "x" + ttos(Modes[i].height) );
        pos_offset += 20.f;
        centerTextOnxAxis(t, pos_offset);

        Button b;
        b.txt = t;
        b.f = static_cast<void (Menu::*)()>(&OptionMenu::changeResolution);
        option.push_back(b);
    }
    t.setCharacterSize(32);
    pos_offset += 40.f;
    //---

    t.setString("Return to main menu");
    centerTextOnxAxis(t,pos_offset);
    option.resize(option.size()+1);
    option.back().txt = t;
    option.back().f = &Menu::exit;
}

OptionMenu::~OptionMenu()
{
    //dtor
}

void OptionMenu::initPosition(){
    Menu::initPosition();
    recenterOptions();
}

void OptionMenu::changeResolution()
{
    int opt = optionClicked-offset_opt_resolution;
    if(opt < 0 || (unsigned int)opt >= sf::VideoMode::getFullscreenModes().size()){
        return;
    }
    //window = sf::RenderWindow(window(sf::VideoMode(1600, 900), "Dodger King",sf::Style::Fullscreen);
    sf::VideoMode videomode = sf::VideoMode::getFullscreenModes()[opt];
    if(videomode.isValid()){
        window.create(videomode, "Dodger King");
        initPosition();
    }

}
