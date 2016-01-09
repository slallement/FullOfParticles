#include "../include/Game.h"

#include <fstream>

void Game::write()
{
}

void Game::read()
{
   /* std::cout<<"lua script"<<std::endl;
    // create new Lua state
    lua_State *lua_state;
    lua_state = luaL_newstate();

    // load Lua libraries
    static const luaL_Reg lualibs[] =
    {
        { "base", luaopen_base },
        { NULL, NULL}
    };

    const luaL_Reg *lib = lualibs;
    for(; lib->func != NULL; lib++)
    {
        lib->func(lua_state);
        lua_settop(lua_state, 0);
    }

    // run the Lua script -----------------------------------------------------
    luaL_dofile(lua_state, "ressources/script/test1.lua");

    // close the Lua state ----------------------------------------------------
    lua_close(lua_state);*/

}

Generator* Game::setNextVisualisation(int* id)
{
    const unsigned int GEN_MAX = 9;
    Generator* ngen=NULL;
    (*id)+=1;
    if((unsigned int)(*id)>GEN_MAX)
        *id = 1;
    switch(*id){
        case 1:
            ngen = new Generator1(&bullet);
            break;
        case 2:
            ngen = new Generator2(&bullet);
            break;
        case 3:
            ngen = new Generator3(&bullet);
            break;
        case 4:
            ngen = new Generator4(&bullet);
            break;
        case 5:
            ngen = new Generator5(&bullet);
            break;
        case 6:
            ngen = new Generator6(&bullet);
            break;
        case 7:
            ngen = new Generator7(&bullet);
            break;
        case 8:
            ngen = new Generator8(&bullet);
            break;
        case 9:
            ngen = new Generator9(&bullet);
            break;
        case 10:
            ngen = new Generator10(&bullet);
            break;
        default:
            ngen = NULL;
    }
    if(ngen == NULL)
        return NULL;
    ngen->getSprite().setPosition(window.getSize().x/2,300.f);
    return ngen;

}

Generator* Game::setNextVisualisation(int* id, std::vector<float> const& args)
{

    Generator* ngen=NULL;
    /*(*id)+=1;
    if(*id>4)
        *id = 1;*/
    switch(*id){
        case 1:
            ngen = new Generator1(&bullet,
                                  static_cast<float>(args[0]),
                                  static_cast<float>(args[1]));
            break;
        case 2:
            ngen = new Generator2(&bullet,
                                  static_cast<float>(args[0]),
                                  static_cast<float>(args[1]),
                                  static_cast<float>(args[2]));
            break;
        case 3:
            ngen = new Generator3(&bullet,
                                  static_cast<float>(args[0]),
                                  static_cast<float>(args[1]),
                                  static_cast<float>(args[2]),
                                  static_cast<float>(args[3]),
                                  static_cast<float>(args[4]));
            break;
        case 4:
            ngen = new Generator4(&bullet,
                                  static_cast<float>(args[0]),
                                  static_cast<float>(args[1]),
                                  static_cast<float>(args[2]),
                                  static_cast<float>(args[3]),
                                  static_cast<float>(args[4]));
            break;
        case 5:
            ngen = new Generator5(&bullet,
                                  static_cast<float>(args[0]),
                                  static_cast<float>(args[1]),
                                  static_cast<float>(args[2]),
                                  static_cast<float>(args[3]),
                                  static_cast<float>(args[4]),
                                  0.1f, 0.f);
            break;
        case 6:
            ngen = new Generator6(&bullet);
            break;
        case 7:
            ngen = new Generator7(&bullet);
            break;
        case 8:
            ngen = new Generator8(&bullet);
            break;
        case 9:
            ngen = new Generator9(&bullet);
        case 10:
            ngen = new Generator10(&bullet);
        default:
            ngen = NULL;
    }
    if(ngen == NULL)
        return NULL;
    ngen->getSprite().setPosition(window.getSize().x/2,300.f);
    return ngen;

}

inline void Game::setVisuText(sf::Text* text, int pos,std::vector<float> const& args)
{
    std::string s("");
    for(unsigned int i=0;i<args.size();++i){
        float val = (float)((int)(args[i]*1000.f)/1000.f);
        if((int)i!=pos){
            s += "  ";
        }else{
            s += "> ";
        }
        s+=ttos(val);
        s+='\n';
    }
    text->setString(s);
}


inline void Game::saveVisualisation()
{
    std::ofstream file( "fichier.txt", std::ios_base::app );
    file << "Une ligne\n";
}

void Game::visualize()
{
    window.setFramerateLimit(FR_LIMIT);
    bool playable = true;
    bool end = false;

    int idgen = 1;
    // ---------------------
    Generator* gen = new Generator10(&bullet);
    // ---------------------
    if(!playable || true)
        gen->getSprite().setPosition(window.getSize().x/2,window.getSize().y/2);
    else
        gen->getSprite().setPosition(window.getSize().x/2,300.f);

    if(playable){
        initPlayer();
    }

    // information text for the visualisation
    sf::Text txt_info;
    txt_info.setFont(*FontManager::getFont("ressources/Symtext.ttf"));
    txt_info.setCharacterSize(12);
    txt_info.setString("M");
    txt_info.setPosition(20,
                         20);
    txt_info.setString("");

    sf::Clock telapsed;
    txt_time.setPosition(window.getSize().x-200,10);
    std::vector<float> args;args.resize(5,1.f);
    int pos = 0;
    setVisuText(&txt_info, pos, args);

    while (window.isOpen() && !end)
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape)
                {
                    end = true;
                }
                if (event.key.code == sf::Keyboard::BackSpace)
                {
                    playable = !playable;
                }
                if (event.key.code == sf::Keyboard::Return)
                {
                    delete gen;
                    gen = setNextVisualisation(&idgen);
                }
            }
            if(playable){
                if (event.type == sf::Event::KeyPressed){
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
            }else{
                if (event.type == sf::Event::KeyPressed){
                    if (event.key.code == sf::Keyboard::S){
                        saveVisualisation();
                    }
                    if (event.key.code == sf::Keyboard::Up)
                        pos--;
                    if (event.key.code == sf::Keyboard::Down)
                        pos++;
                    if (event.key.code == sf::Keyboard::Left)
                        args[pos] -= 0.1f;
                    if (event.key.code == sf::Keyboard::Right)
                        args[pos] += 0.1f;
                    if(pos>=(int)args.size())
                        pos = 0;
                    if(pos<0)
                        pos = (int)args.size()-1;

                    if (event.key.code == sf::Keyboard::Up
                        || event.key.code == sf::Keyboard::Down
                        || event.key.code == sf::Keyboard::Right
                        || event.key.code == sf::Keyboard::Left )
                    {
                        setVisuText(&txt_info, pos, args);
                        delete gen;
                        gen = setNextVisualisation(&idgen,args);
                    }
                }
            }

        }

        // update data
        window.clear();

        if(gen != NULL)
            gen->update(dt);

        if(playable){
            // move the player
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                player.update(0.5f*dt);
            else
                player.update(dt);
            window.draw(player);
            // detect bullet collisions
            manageBulletCollision();
            txt_time.setString("Temps écoulé: "+ttos(telapsed.getElapsedTime().asSeconds())
                           +"\nVies: "+ttos(player.getLives())
                            +"\nfps: "+ttos(getFrameRate()) );
            for(int i=(int)bulletPlayer.size()-1;i>=0;i--){
                bulletPlayer[i].update(dt);
                window.draw(bulletPlayer[i]);
            }
        }else{
            manageBulletCollision();
            txt_time.setString("Temps écoulé: "+ttos(elapsed.getElapsedTime().asSeconds())
                            +"\nfps: "+ttos(getFrameRate()) );
        }

        if(bullet.size() > 0)
            for(int i=(int)(bullet.size())-1;i>=0;i--){
                bullet[i].update(dt);
                window.draw(bullet[i]);
            }

        window.draw(txt_time);
        window.draw(txt_info);

        window.display();
    }
}


