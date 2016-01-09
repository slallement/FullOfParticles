#include "../include/Game.h"

Game::Game(sf::RenderWindow & win) :
    window(win), bullet(), bulletPlayer(), enemies(), player(3),
    initialized(true), nbKill(0), missionTime(0.f)
{
    init();
    mission = new Mission1(this);
}

Game::Game(sf::RenderWindow & win, Mission const& miss) :
    window(win), bullet(), bulletPlayer(), enemies(), player(3),
    initialized(true), nbKill(0), missionTime(0.f)
{
    init();
    *mission = miss;
}

Game::~Game(){}

void Game::init()
{
    window.setFramerateLimit(FR_LIMIT);
    dt = 1.f/FR_LIMIT;
    makePlayer();

    txt_time.setFont(*FontManager::getFont("ressources/Symtext.ttf"));
    txt_time.setCharacterSize(12);
    shader_retro.loadFromFile("shaders/retro1.vert","shaders/retro1.frag");
    shader_blur1.loadFromFile("shaders/gblur.vert","shaders/gblur.frag");
        /*shader_blur1.setParameter("horizontal",1);
        shader_blur1.setParameter("texture_size",layer_bullet_enemies.getSize().x,
                                  layer_bullet_enemies.getSize().y);*/

    if (!layer_game.create(window.getDefaultView().getSize().x,window.getDefaultView().getSize().y))
        initialized = false;
    layer_game.setView(window.getDefaultView());
    if (!layer_bullet_enemies.create(window.getDefaultView().getSize().x,
                                      window.getDefaultView().getSize().y))
        initialized = false;

    //read();
}

inline void Game::makePlayer()
{
    /*player.getSprite().setTexture(
        *TextureManager::getTexture("ressources/img/ship1.png"));
    player.setRotation(180.f);
    player.getSprite()
    player.clearWeapon();
    */
    player.setBaseWeapon(bulletPlayer);
}

void Game::initPlayer()
{
    player.setPosition((window.getDefaultView().getSize().x-player.getSprite().getGlobalBounds().width)/2,
                       window.getDefaultView().getSize().y-100.f);
    player.setV(0.f,0.f);
}

void Game::clear()
{
    enemiesStored.clear();
    programmed.clear();
    bullet.clear();
    bulletPlayer.clear();

    for( std::list<BulletModifier*>::const_iterator it=bmodifier_enemies.begin(),
        e=bmodifier_enemies.end(); e!=it;++it)
    {
        delete *it;
    }
    bmodifier_enemies.clear();
}

unsigned int Game::storeModel(ShipEnemy const& element){
    enemiesStored.push_back(element);
    return enemiesStored.size()-1;
}

void Game::addToProgrammation(ShipEnemy const* element, float time){
    enemiesStored.push_back(*element);
    //programmed.push_back({time,&enemiesStored.back()});
    programmed.push_back(ScheduledShip());
    programmed.back().time = time;
    programmed.back().ship = &enemiesStored.back();
}

void Game::addToProgrammation(unsigned int id, float time){
    if(id > enemiesStored.size()){
        return; // error
    }
    //programmed.push_back({time,&enemiesStored[id]});
    programmed.push_back(ScheduledShip());
    programmed.back().time = time;
    programmed.back().ship = &enemiesStored[id];
}

void Game::addToProgrammation(unsigned int id, float time, sf::Vector2f pos)
{
    if(id > enemiesStored.size()){
        return; // error
    }
    programmed.push_back(ScheduledShip());
    programmed.back().time = time;
    programmed.back().ship = &enemiesStored[id];
    programmed.back().pos = pos;
}

/* add objects in the current game at the programmed time*/
inline void Game::addProgrammedInGame(float t)
{
    while(t >= programmed.front().time && programmed.size() > 0){
        enemies.push_back(*programmed.front().ship);
        // set the position if it's valid
        if(programmed.front().pos.x > -50.f){
            enemies.back().setPosition(programmed.front().pos);
        }
        programmed.pop_front();
    }
}

void Game::sortProgrammation()
{
    sort(programmed.begin(),programmed.end(),ScheduledShip::comp);
}

void Game::addAttractor()
{
    bmodifier_enemies.push_back(
        new Attractor(&bullet,150, player.getSprite().getPosition(),60.f,10.f));
}

void Game::manageBmodifier()
{
    for( std::list<BulletModifier*>::iterator it=bmodifier_enemies.begin();
        it!=bmodifier_enemies.end(); ++it)
    {
        (*it)->update(dt);
        layer_game.draw(**it);
        if((*it)->isInactive()){
            it = bmodifier_enemies.erase(it);
        }
    }
}

inline void Game::manageMission()
{
    // reset time if the mission's mode changes
        if(currentMode != mission->getMode()){
            elapsed.restart();
            missionTime = 0.f;
            //time2 = 0.f;
            currentMode = mission->getMode();
        }
        if(mission->getMode() == MissionState::NORMAL
           || mission->getMode() == MissionState::ENDING ){
            missionTime += dt;
            //addProgrammedInGame(missionTime);
            addProgrammedInGame(mission->getElapsedTime());
        }else if(mission->getMode() == MissionState::DEATHMATCH){
            if(enemies.size() <= 0){
                missionTime += dt;
                //addProgrammedInGame(missionTime);
                addProgrammedInGame(mission->getElapsedTime());
            }
        }
}

inline void Game::mainEvent()
{
    if (event.type == sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::Escape)
        {
            mission->abort();
        }
        if (event.key.code == sf::Keyboard::Pause)
        {
            if(dt > 0.f) {
                dt = 0.f;
            }else{
                dt = 1.f/FR_LIMIT;
            }
        }
        if (event.key.code == sf::Keyboard::Right
            || event.key.code == sf::Keyboard::Left
            || event.key.code == sf::Keyboard::Down
            || event.key.code == sf::Keyboard::Up
            )
        {
            float x=0.f, y=0.f;
            if (event.key.code == sf::Keyboard::Right)
                x = 1.f;
            if (event.key.code == sf::Keyboard::Left)
                x = -1.f;
            if (event.key.code == sf::Keyboard::Down)
                y = 1.f;
            if (event.key.code == sf::Keyboard::Up)
                y = -1.f;
            player.move(x,y);
        }

        if (event.key.code == sf::Keyboard::Numpad0){
            addAttractor();
        }
        if (event.key.code == sf::Keyboard::Numpad1){
            bmodifier_enemies.push_back(
                  new Destroyer(&bullet,100, player.getSprite().getPosition()));
        }
        if (event.key.code == sf::Keyboard::K){ // suicide
            while(player.getLives()>0)
                player.hit();
        }
        if (event.key.code == sf::Keyboard::Space){
            player.focus();
        }

    }
    if (event.type == sf::Event::KeyReleased){
        if (event.key.code == sf::Keyboard::Right && player.getV().x>0.f)
            player.stop(true);
        if (event.key.code == sf::Keyboard::Left && player.getV().x<0.f)
            player.stop(true);
        if (event.key.code == sf::Keyboard::Down && player.getV().y>0.f)
            player.stop(false);
        if (event.key.code == sf::Keyboard::Up && player.getV().y<0.f)
            player.stop(false);
        if (event.key.code == sf::Keyboard::Space){
            player.unfocus();
        }

        if (event.key.code == sf::Keyboard::Pause)
        {

        }
    }
}

void Game::initMission()
{

}

bool Game::run()
{
    try{
        // initialization
        if(!initialized)
            return false;

        mission->init();
        bg.load(mission->getBackground());

        initPlayer();

        txt_time.setPosition(window.getDefaultView().getSize().x-200,10);

        window.setFramerateLimit(FR_LIMIT);

        currentMode = mission->getMode();
        //elapsed.restart();

    }catch(const std::exception &e){
        std::cerr<<e.what()<<std::endl;
        return false;
    }catch (const std::string& ex) {
        std::cerr<<ex<<std::endl;
        return false;
    } catch (...) {
        std::cerr<<"Error on initialization."<<std::endl;
        return false;
    }

    elapsed_info.restart();

    while (window.isOpen() && mission->isContinuing())
    {
        //float time = elapsed.getElapsedTime().asSeconds();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                mission->abort();
                window.close();
                continue;
            }
            if (event.type == sf::Event::Resized){
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            }
            else
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::G){
                    return true;
                }
            }
            mainEvent();
        }

        manageMission();
        if(player.getLives() <= 0)
        {
            mission->abort();
            continue;
        }

        layer_game.clear();
        layer_game.draw(bg);

        mission->update(dt);

        manageBmodifier();

        player.getEquipment()->update(dt);
        drawEnemies();

        layer_game.draw(*player.getEquipment());

        // draw bullets
        if(mission->getMode() != MissionState::ENDING){
            // draw enemies bullet
            layer_bullet_enemies.clear(sf::Color::Transparent);

            if(bullet.size() > 0)
                for(int i=(int)(bullet.size())-1;i>=0;i--){
                    bullet[i].update(dt);
                    layer_bullet_enemies.draw(bullet[i]);
                }

            // draw player bullets
            if( bulletPlayer.size() > 0)
                for(int i=(int)bulletPlayer.size()-1;i>=0;i--){
                    bulletPlayer[i].update(dt);
                    layer_game.draw(bulletPlayer[i]);
                }
            layer_bullet_enemies.display();

            layer_game.draw(sf::Sprite(layer_bullet_enemies.getTexture()));
        }

        for(unsigned int i=0;i<bonus.size();++i){
            bonus[i].update(dt);
            layer_game.draw(bonus[i]);
        }

        for(std::deque<Entity*>::iterator it=decor.begin();it!=decor.end();){
            (*it)->update(dt);
            layer_game.draw(**it);
            if(!(*it)->isActive()){
                it = decor.erase(it);
            }else{
                ++it;
            }
        }

        // test collisions
        manageBulletCollision();
        manageBonus();

        // information text
        txt_time.setString("Temps écoulé: "+ttos(elapsed_info.getElapsedTime().asSeconds())
                           +"\nVies: "+ttos(player.getLives())
                           +"\nDef: "+ttos(player.getShiled()->getDefense())
                           +"\nfps: "+ttos(getFrameRate()) );
        shader_retro.setParameter("textureSize",txt_time.getLocalBounds().width,
                                    txt_time.getLocalBounds().height);
        layer_game.draw(txt_time,&shader_retro);
        layer_game.display();

        drawAll();
        if(dt<=0.f){
            pauseScreen();
        }
        window.display();
    }

    //game over screen
    bool failure = mission->hasFail();
    if(failure && window.isOpen()){
        sf::Texture screen;
        screen.loadFromImage(window.capture());
        showFailure(screen);
    }

    // clean memory
    delete mission;
    mission = 0;// NULL
    clear();
    return !failure;
}

void Game::drawAll()
{
    // draw game_layer on the screen
    window.clear();
    layer_game_s.setTexture(layer_game.getTexture());
    if(player.getTimeLastHit() > 0.f){
        // if the player is hit
        sf::Vector2f v = sf::Vector2f( (1.f-0.9f*cos(player.getTimeLastHit()*TWO_PI*10.f))*window.getSize().x,
                                       1.f*window.getSize().y);
        shader_retro.setParameter("textureSize",v);
    }else if(player.getLives() <= 0){
        // if gameover
        sf::Vector2f v = sf::Vector2f( (1.f-0.9f*cos(elapsed_info.getElapsedTime().asSeconds()*TWO_PI*10.f))*window.getSize().x,
                                       1.f*window.getSize().y);
        shader_retro.setParameter("textureSize",v);
    }else{
        // normal
        shader_retro.setParameter("textureSize",sf::Vector2f(window.getSize()));
    }
    window.draw(layer_game_s,&shader_retro);
}

void Game::pauseScreen(){
    // pause menu
    sf::RectangleShape bg_black(sf::Vector2f(window.getSize()));
    bg_black.setFillColor(sf::Color(0,0,0,200));
    sf::Text pause_info("Pause",*FontManager::getFont("ressources/Symtext.ttf"),28);
    bg_black.setScale(window.getDefaultView().getSize().x/window.getSize().x,
                        window.getDefaultView().getSize().y/window.getSize().y);
    pause_info.setPosition((window.getDefaultView().getSize().x-pause_info.getGlobalBounds().width)/2.f,
                           (window.getDefaultView().getSize().y-pause_info.getGlobalBounds().height)/2.f);
    window.draw(bg_black);
    window.draw(pause_info);
}

// show game over
void Game::showFailure(sf::Texture screen)
{
    const float DURATION = 6.f;
    bool running = true;
    sf::Sprite scene_bg(screen);
    // avoid problems with the window rescaling
    scene_bg.setScale(window.getDefaultView().getSize().x/window.getSize().x,
                      window.getDefaultView().getSize().y/window.getSize().y);
    sf::Shader effect;
    effect.loadFromFile("shaders/base.vert","shaders/gameover1.frag");
    sf::Text info("Game Over",*FontManager::getFont("ressources/Symtext.ttf"),78);
    info.setPosition( (window.getDefaultView().getSize().x-info.getGlobalBounds().width)/2.f,
                      (window.getDefaultView().getSize().y-info.getGlobalBounds().height)/2.f);
    float telapsed = 0.f;

    while (window.isOpen() && running)
    {
        //float time = elapsed.getElapsedTime().asSeconds();
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape){
                    running = false;
                }
            }
        }

        if(telapsed >= DURATION){
            running = false;
        }
        telapsed += dt;
        effect.setParameter("time",telapsed);
        window.draw(scene_bg,&effect);
        window.draw(info);
        window.display();
    }
}

void Game::drawEnemies()
{
    // update all enemies and draw them on screen
    for (std::list<ShipEnemy>::iterator it=enemies.begin();
            it != enemies.end(); ++it)
    {
        it->update(dt);
        layer_game.draw(*it);
        // out of screen
        if(it->getSprite().getGlobalBounds().top > layer_game.getSize().y){
            it = enemies.erase(it);
        }
    }
}

/* test collisions with the bullets */
void Game::manageBulletCollision(){
    // enemies bullet
    for (std::deque<Bullet>::iterator bul=bullet.begin(); bul != bullet.end();){
        // if bullet out of screen
        if(!bul->getSprite().getGlobalBounds().intersects(
                sf::FloatRect(-1.f,-1.f,
                window.getDefaultView().getSize().x,
                window.getDefaultView().getSize().y)) )
        {
            bul = bullet.erase(bul);
        }else
        // if bullet collide with the player spaceship
        if(bul->getSprite().getGlobalBounds().intersects(getPlayerHitbox()))
        {
            bul = bullet.erase(bul);
            //player.getShiled()->hit();
            player.getEquipment()->hit();
        }else
            ++bul;

    }

    #ifdef DEBUG
    sf::RectangleShape rect(sf::Vector2f(getPlayerHitbox().width,getPlayerHitbox().height));
    rect.setFillColor(sf::Color(0,0,0,0));
    rect.setOutlineThickness(1);
    rect.setOutlineColor(sf::Color(255,0,0));
    rect.setPosition(player.getSprite().getPosition().x-getPlayerHitbox().width/2,
                     player.getSprite().getPosition().y
                     -player.getSprite().getLocalBounds().height/2-getPlayerHitbox().height/2);
    layer_game.draw(rect);
    #endif

    // player's bullet
    for (std::deque<Bullet>::iterator bul=bulletPlayer.begin(); bul != bulletPlayer.end(); ){
        // if bullet out of screen
        if(!bul->getSprite().getGlobalBounds().intersects(
            sf::FloatRect(-1.f,-1.f,window.getDefaultView().getSize().x,
                          window.getDefaultView().getSize().y)) )
        {
           bul = bulletPlayer.erase(bul);
        }else{
            bool hit = false;
            // if it shoot an  ennemy
            for (std::list<ShipEnemy>::iterator it=enemies.begin(); it != enemies.end(); ++it){
                if(bul->getSprite().getGlobalBounds().intersects(
                sf::FloatRect(it->getSprite().getGlobalBounds()) ))
                {
                    it->hit();
                    if(it->getLives() <= 0){

                        putBonus((*it));
                        // effect of explosion
                        decor.push_back(new EffectExplosion(it->getPos(),*(*it).getSprite().getTexture()));
                        /*decor.back()->setTexture(
                                *(*it).getSprite().getTexture(),true);*/
                        it = enemies.erase(it);
                        nbKill++;

                    }
                    hit = true;
                    bul = bulletPlayer.erase(bul);
                    break;
                }
            }

            if(!hit)
                bul++;
        }
    }
}

inline void Game::putBonus(Ship& it)
{
    /*{
        bonus.push_back(ShipBonus(ShipBonus::IMPROVE_RATE1));
        bonus.back().getSprite().setPosition(it.getSprite().getPosition());
        return;
    }*/
    if(it.getLivesMax() < 8){
        float luck = rand() % 100;
        if(luck < 20){
            bonus.push_back(ShipBonus(ShipBonus::LIFE_LV1));
            bonus.back().getSprite().setPosition(it.getSprite().getPosition());
        }else if (luck < 30){
            bonus.push_back(ShipBonus(ShipBonus::SHILED_LV1));
            bonus.back().getSprite().setPosition(it.getSprite().getPosition());
        }
    }else{
        //float luck = rand() % ;
        int points = it.getLivesMax();
        static const unsigned int possibilities[] = {0,1,
                                            ShipBonus::SHILED_LV1,30,
                                            ShipBonus::LIFE_LV1,40,
                                            ShipBonus::IMPROVE_RATE1,200};
        static const unsigned int possibilities_size =  sizeof(possibilities)/sizeof(possibilities[0])/2;
        unsigned int best = 0;
        while(points>=(int)possibilities[2*best+1])
        {
            ++best;
        }
        if(best >= possibilities_size) { // avoid beeing out of bounds
            best = possibilities_size-1;
        }
        if(best == 0){
            return;
        }
        // best >= 1 here
        bonus.push_back(ShipBonus(possibilities[2*best]));
        bonus.back().getSprite().setPosition(it.getSprite().getPosition());
        points -= possibilities[2*best+1];

        while(points > 0 && best >= 1){
            unsigned int luck = rand()%best;
            if(luck > 0){
                bonus.push_back(ShipBonus(possibilities[2*luck])); // crash ?
                bonus.back().getSprite().setPosition(
                                                it.getSprite().getPosition());
                float dx = 100.f*((float)rand()/(float)RAND_MAX-0.5f);
                float dy = 40.f*((float)rand()/(float)RAND_MAX-0.5f);
                bonus.back().getSprite().move(dx,dy);
            }
            points -= possibilities[2*luck+1];
        }
    }
}

inline sf::FloatRect Game::getPlayerHitbox()
{
    return sf::FloatRect(player.getSprite().getPosition().x-5.f,
                         player.getSprite().getPosition().y
                         -player.getSprite().getLocalBounds().height*0.5f-5.f,
                         10.f,
                         10.f);
}

inline void Game::manageBonus()
{
    for(unsigned int i=0;i<bonus.size();++i){
        if(bonus[i].getSprite().getGlobalBounds().intersects(getPlayerHitbox()))
        {
            bonus[i].affect(player);
            bonus.erase(bonus.begin()+i);
            i++;
        }
    }
}

unsigned int Game::getFrameRate()
{
    static unsigned int frameCounter = 0;
    static float frameTime = 0.f;
    static unsigned int fps = 0;
    static sf::Clock clock;
    frameTime += clock.restart().asSeconds();
    frameCounter++;
    if(frameTime >= 1.f)
    {
        fps = frameCounter;
        frameCounter = 0;
        frameTime -= 1.f;
    }
    return fps;
}

int Game::getRemainingEnnemyLife() const {
    if(enemies.size()<=0)
        return 0;
    int r=0;
    for(std::list<ShipEnemy>::const_iterator it=enemies.begin();
            it!=enemies.end();
            ++it)
    {
        r += it->getLives();
    }
    return r;
    //return (enemies.size()>0) ? (int)enemies.front().getLives() : 0;
}

int Game::getRemainingEnnemyLifeMax() const {
    if(enemies.size()<=0)
        return 0;
    int r=0;
    for(std::list<ShipEnemy>::const_iterator it=enemies.begin();
            it!=enemies.end();
            ++it)
    {
        r += it->getLivesMax();
    }
    return r;
    //return (enemies.size()>0) ? (int)enemies.front().getLivesMax() : 0;
}
