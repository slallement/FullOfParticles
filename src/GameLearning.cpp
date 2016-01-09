#include "../include/Game.h"

GameLearn::GameLearn(sf::RenderWindow & w) : Game(w), model(1000,150.f)
{
    model.setTexture(*TextureManagerGlobal::getTexture("ressources/img_ship/ship6.png"),true);
    model.setPosition(window.getSize().x/2.f,100.f);
    model.addWeapon(new Generator1(&bullet));
    makePlayer();
}

void GameLearn::init()
{


}

void GameLearn::makePlayer()
{
    player.setBaseWeapon(bulletPlayer);
    player.addWeapon(new Generator3(&bulletPlayer, 0.1f, 8, 4, 0.1f, 0.2f));

}

void GameLearn::learn()
{
    learnInvisible();
    /* */
    enemies.push_back(model);
    ShipEnemy* body = &enemies.back();

    std::vector<ShipEvolutive> evo;
    for(int i=0;i<NB_INDIVIDUALS;i++){
        std::string str = "P"+ttos(i);
        evo.push_back(ShipEvolutive(body,str));
    }
    for(unsigned int i=0;i<evo.size();i++){
        evo[i].setBulletPlayer(&bulletPlayer);
    }
    int current = 0;
    float bestTime = 0.f;

    /* */
    bool end=false;
    window.setFramerateLimit(FR_LIMIT);
    initPlayer();

    sf::Clock telapsed;
    txt_time.setPosition(window.getSize().x-200,10);
    dt = 1.f/FR_LIMIT;
    static const float offsetsecurity = body->getVelocity()*dt*1.2f+10.f;

    while (window.isOpen() && !end)
    {
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();

                if (event.type == sf::Event::KeyPressed){
                    if (event.key.code == sf::Keyboard::Escape)
                        end = true;

                    if (event.key.code == sf::Keyboard::Right)
                        player.setVx(player.getVelocity());
                    if (event.key.code == sf::Keyboard::Left)
                        player.setVx(-player.getVelocity());
                    if (event.key.code == sf::Keyboard::Down)
                        player.setVy(player.getVelocity());
                    if (event.key.code == sf::Keyboard::Up)
                        player.setVy(-player.getVelocity());

                }
                if (event.type == sf::Event::KeyReleased){
                    if (event.key.code == sf::Keyboard::Right && player.getV().x>0.f)
                        player.setVx(0.f);
                    if (event.key.code == sf::Keyboard::Left && player.getV().x<0.f)
                        player.setVx(0.f);
                    if (event.key.code == sf::Keyboard::Down && player.getV().y>0.f)
                        player.setVy(0.f);
                    if (event.key.code == sf::Keyboard::Up && player.getV().y<0.f)
                        player.setVy(0.f);
                }


        }

        // update data

        layer_game.clear();

        if(body->getLives()<=LIFE_SECURITY-LIFE_INDIVIDUALS){
            current++;
            if(current >= (int)evo.size()){
                current = 0;
                bestTime = ShipEvolutive::reproduction(evo);
            }
            body->addLife(LIFE_SECURITY-body->getLives());
            body->setPosition(layer_game.getSize().x/2.f,100.f);
            body->setV(0.f,0.f);

            //ennemies.push_back(model3);
            //body = &ennemies.back();

            evo[current].reset();
        }
        if(body->getSprite().getPosition().x < offsetsecurity)
            body->setPosition(offsetsecurity,body->getSprite().getPosition().y);
        if(body->getSprite().getPosition().y < offsetsecurity)
            body->setPosition(body->getSprite().getPosition().x,offsetsecurity);
        if(body->getSprite().getPosition().x > layer_game.getSize().x-offsetsecurity)
            body->setPosition(layer_game.getSize().x-offsetsecurity,body->getSprite().getPosition().y);
        if(body->getSprite().getPosition().y > layer_game.getSize().y-offsetsecurity)
            body->setPosition(body->getSprite().getPosition().x,layer_game.getSize().y-offsetsecurity);
        evo[current].update(dt);

        // move the player
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            player.update(2.5f*dt);
        else
            player.update(dt);
        layer_game.draw(player);

        for (std::list<ShipEnemy>::iterator it=enemies.begin(); it != enemies.end(); ++it){
            it->update(dt);
            layer_game.draw(*it);
            // out of screen
            if(it->getSprite().getGlobalBounds().top > layer_game.getSize().y){
                //it = ennemies.erase(it);
            }
        }
        // detect bullet collisions
        manageBulletCollision();
        std::string info("");
        for(unsigned int i=0;i<evo.size();i++)
            info += evo[i].getName()+">"+ttos(evo[i].getTime())+"\n";
        txt_time.setString("Temps écoulé: "+ttos(telapsed.getElapsedTime().asSeconds())
                       +"\nVies: "+ttos(player.getLives())
                        +"\nfps: "+ttos(getFrameRate())
                           +"\n ENT: "+evo[current].getName()
                           +"\n GEN: "+ttos(evo[current].getGeneration())
                           +"\n BestTile: "+ttos(bestTime)
                            +"\n"+info
                           );
        for(int i=(int)bulletPlayer.size()-1;i>=0;i--){
            bulletPlayer[i].update(dt);
            layer_game.draw(bulletPlayer[i]);
        }

        if(bullet.size() > 0)
            for(int i=(int)(bullet.size())-1;i>=0;i--){
                bullet[i].update(dt);
                layer_game.draw(bullet[i]);
            }
        layer_game.display();
        window.clear();
        window.draw(sf::Sprite(layer_game.getTexture()));

        window.draw(txt_time);
        window.display();
    }

    for(unsigned int i=0;i<evo.size();++i){
        evo[i].writeGenome();
    }

}

void GameLearn::learnInvisible()
{
    const unsigned int TIME_WAITING = 60.f; // in sec

    window.setFramerateLimit(0);

    enemies.push_back(model);
    Ship* body = &enemies.back();

    std::vector<ShipEvolutive> evo;
    for(int i=0;i<NB_INDIVIDUALS;i++){
        std::string str = "P"+ttos(i);
        evo.push_back(ShipEvolutive(body,str));
    }
    for(unsigned int i=0;i<evo.size();i++){
        evo[i].setBulletPlayer(&bulletPlayer);
    }
    int current = 0;
    float bestTime = 0.f;
    float bestTimeCumul = 0.f;

    dt = 1.f/FR_LIMIT;

    sf::Text info;
    info.setFont(*FontManager::getFont("ressources/Symtext.ttf"));
    info.setCharacterSize(12);
    info.setPosition(window.getSize().x/2,10);

    static const float offsetsecurity = body->getVelocity()*dt*1.2f+10.f;
    float tcounter = -2.f;
    int gencounter = 1; // generation counter
    int ncounter = 0;
    bool end = false;

    initPlayer();

    sf::Clock telapsed;
    while (window.isOpen() && !end && telapsed.getElapsedTime().asSeconds() < TIME_WAITING){
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape)
                    end = true;
            }
        }

        // update data

        if(body->getLives() <= LIFE_SECURITY-LIFE_INDIVIDUALS){
            // next individual
            current++;
            if(current >= (int)evo.size()){
                current = 0;
                bestTime = ShipEvolutive::reproduction(evo);
                bestTimeCumul += bestTime;
                gencounter++;
            }

            body->addLife(LIFE_SECURITY-body->getLives());
            body->setPosition(layer_game.getSize().x/2.f,100.f);
            body->setV(0.f,0.f);

            //ennemies.push_back(model3);
            //body = &ennemies.back();

            evo[current].reset();
        }
        if(body->getSprite().getPosition().x < offsetsecurity)
            body->setPosition(offsetsecurity,body->getSprite().getPosition().y);
        if(body->getSprite().getPosition().y < offsetsecurity)
            body->setPosition(body->getSprite().getPosition().x,offsetsecurity);
        if(body->getSprite().getPosition().x > layer_game.getSize().x-offsetsecurity)
            body->setPosition(layer_game.getSize().x-offsetsecurity,body->getSprite().getPosition().y);
        if(body->getSprite().getPosition().y > layer_game.getSize().y-offsetsecurity)
            body->setPosition(body->getSprite().getPosition().x,layer_game.getSize().y-offsetsecurity);
        evo[current].update(dt);

        // move the player
        player.update(dt);

        for (std::list<ShipEnemy>::iterator it=enemies.begin(); it != enemies.end(); ++it){
            it->update(dt);
            // out of screen
            if(it->getSprite().getGlobalBounds().top > layer_game.getSize().y){
                //it = ennemies.erase(it);
            }
        }
        // detect bullet collisions
        manageBulletCollision();

        for(int i=(int)bulletPlayer.size()-1;i>=0;i--){
            bulletPlayer[i].update(dt);
        }

        if(bullet.size() > 0)
            for(int i=(int)(bullet.size())-1;i>=0;i--){
                bullet[i].update(dt);
            }


        if(elapsed.getElapsedTime().asSeconds()-tcounter > 1.f){
            window.clear();

            // snapshot
            layer_game.clear();
            layer_game.draw(player);
            for (std::list<ShipEnemy>::iterator it=enemies.begin(); it != enemies.end(); ++it){
                layer_game.draw(*it);
            }

            for(int i=(int)bulletPlayer.size()-1;i>=0;i--){
                layer_game.draw(bulletPlayer[i]);
            }

            if(bullet.size() > 0)
                for(int i=(int)(bullet.size())-1;i>=0;i--){
                    layer_game.draw(bullet[i]);
                }

            layer_game.display();
            window.draw(sf::Sprite(layer_game.getTexture()));
            // ---

            std::string info2("");
            for(unsigned int i=0;i<evo.size();i++)
                info2 += evo[i].getName()+">"+ttos(evo[i].getTime())+"\n";
            info.setString("Temps : "+ttos(telapsed.getElapsedTime().asSeconds())+"\n"+
                            "Step : "+ttos(ncounter)+"\n"+
                           "Generation Max : "+ttos(gencounter)+
                           "\nBestTime : "+ttos(bestTime)+
                           "\nAvg : "+ttos(bestTimeCumul/(float)gencounter)
                           //+"\nfps : "+ttos(getFrameRate())+"\n---\n"+info2
                           );
            window.draw(info);
            window.display();
            tcounter = elapsed.getElapsedTime().asSeconds();
        }else
            getFrameRate();
        ncounter++;
    }

    for(unsigned int i=0;i<evo.size();++i){
        evo[i].writeGenome();
    }
    clear();
    enemies.clear();
}

