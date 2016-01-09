
#include "MissionState_1.h"
#include "Utils.h"

MissionState1_1::MissionState1_1(Mission* m, MissionState* n):
    MissionState(m,n), begin(1.f)
{
    mode = NORMAL;
    a1 = 0.f;
    d1 = 1.;
    a2 = 2.f;
    d2 = 3.f;
}

void MissionState1_1::init()
{
    //MissionContext const& scontext = mission->getContext();
    const float winWidth = *context->winWidth;
    // models
    ShipEnemy model1 = ShipEnemy(25,100.f);
    model1.setTexture(*textures.getTexture("ressources/img_ship/ship2.png"),true);
    model1.getSprite().setColor(sf::Color::White);
    /*model1.setVxBehavior(BehaviorAstract::sin200);
    model1.setVyBehavior(BehaviorAstract::cos100f2);*/
    //model1.setVy(10.f);
    //sf::Vector2f x[] = {sf::Vector2f(50.f,20.f),sf::Vector2f(-100.f,40.f),sf::Vector2f(50.f,20.f)};
    //sf::Vector2f x[] = {sf::Vector2f(50.f,0.f),sf::Vector2f(-50.f,20.f),sf::Vector2f(150.f,40.f)};
    sf::Vector2f  x[90]= {sf::Vector2f(4.251259259259257f,0.06992592592592928f), sf::Vector2f(16.25007407407412f,0.3994074074074163f), sf::Vector2f(34.86400000000003f,1.1680000000000135f), sf::Vector2f(58.960592592592604f,2.555259259259273f), sf::Vector2f(87.40740740740739f,4.740740740740748f), sf::Vector2f(119.072f,7.903999999999996f), sf::Vector2f(152.82192592592588f,12.224592592592586f), sf::Vector2f(187.52474074074075f,17.882074074074083f), sf::Vector2f(222.048f,25.055999999999997f), sf::Vector2f(255.25925925925924f,33.925925925925924f), sf::Vector2f(286.026074074074f,44.6714074074074f), sf::Vector2f(313.216f,57.47200000000001f), sf::Vector2f(335.69659259259265f,72.50725925925927f), sf::Vector2f(352.3354074074074f,89.95674074074071f), sf::Vector2f(362.0f,110.0f), sf::Vector2f(362.1078518518518f,128.4791111111111f), sf::Vector2f(351.8494814814816f,141.69955555555555f), sf::Vector2f(332.75200000000007f,150.53600000000003f), sf::Vector2f(306.34251851851866f,155.86311111111112f), sf::Vector2f(274.1481481481482f,158.5555555555556f), sf::Vector2f(237.69600000000003f,159.488f), sf::Vector2f(198.51318518518525f,159.53511111111112f), sf::Vector2f(158.1268148148148f,159.57155555555553f), sf::Vector2f(118.06399999999996f,160.47199999999998f), sf::Vector2f(79.8518518518519f,163.11111111111111f), sf::Vector2f(45.017481481481525f,168.36355555555554f), sf::Vector2f(15.087999999999994f,177.104f), sf::Vector2f(-8.409481481481464f,190.2071111111111f), sf::Vector2f(-23.94785185185185f,208.54755555555556f), sf::Vector2f(-30.0f,233.0f), sf::Vector2f(-25.677333333333337f,256.84503703703706f), sf::Vector2f(-12.058666666666625f,273.49362962962965f), sf::Vector2f(9.432000000000045f,284.0160000000001f), sf::Vector2f(37.37066666666669f,289.48237037037046f), sf::Vector2f(70.33333333333337f,290.96296296296305f), sf::Vector2f(106.89600000000002f,289.528f), sf::Vector2f(145.6346666666667f,286.2477037037037f), sf::Vector2f(185.12533333333334f,282.19229629629626f), sf::Vector2f(223.94399999999996f,278.432f), sf::Vector2f(260.6666666666667f,276.03703703703707f), sf::Vector2f(293.8693333333333f,276.07762962962966f), sf::Vector2f(322.12800000000004f,279.624f), sf::Vector2f(344.0186666666667f,287.7463703703704f), sf::Vector2f(358.11733333333336f,301.51496296296295f), sf::Vector2f(363.0f,322.0f), sf::Vector2f(359.9582222222223f,345.4779259259259f), sf::Vector2f(351.7591111111111f,367.3967407407408f), sf::Vector2f(339.192f,387.584f), sf::Vector2f(323.04622222222235f,405.86725925925936f), sf::Vector2f(304.1111111111112f,422.07407407407425f), sf::Vector2f(283.176f,436.0319999999999f), sf::Vector2f(261.0302222222222f,447.56859259259255f), sf::Vector2f(238.46311111111112f,456.51140740740743f), sf::Vector2f(216.264f,462.688f), sf::Vector2f(195.22222222222223f,465.925925925926f), sf::Vector2f(176.12711111111116f,466.0527407407408f), sf::Vector2f(159.76799999999997f,462.896f), sf::Vector2f(146.93422222222222f,456.28325925925924f), sf::Vector2f(138.41511111111106f,446.04207407407404f), sf::Vector2f(135.0f,432.0f), sf::Vector2f(135.8915555555555f,416.7638518518518f), sf::Vector2f(139.49244444444446f,403.07081481481487f), sf::Vector2f(145.39200000000005f,390.9440000000001f), sf::Vector2f(153.17955555555568f,380.40651851851857f), sf::Vector2f(162.44444444444446f,371.4814814814816f), sf::Vector2f(172.776f,364.192f), sf::Vector2f(183.76355555555557f,358.56118518518514f), sf::Vector2f(194.99644444444436f,354.61214814814815f), sf::Vector2f(206.06400000000002f,352.368f), sf::Vector2f(216.55555555555554f,351.85185185185185f), sf::Vector2f(226.06044444444444f,353.08681481481483f), sf::Vector2f(234.168f,356.096f), sf::Vector2f(240.46755555555558f,360.9025185185186f), sf::Vector2f(244.54844444444444f,367.5294814814815f), sf::Vector2f(246.0f,376.0f), sf::Vector2f(245.42103703703702f,385.2494814814815f), sf::Vector2f(243.76829629629634f,394.12918518518524f), sf::Vector2f(241.16800000000006f,402.5360000000001f), sf::Vector2f(237.7463703703704f,410.3668148148149f), sf::Vector2f(233.62962962962968f,417.5185185185186f), sf::Vector2f(228.94400000000002f,423.8879999999999f), sf::Vector2f(223.81570370370366f,429.37214814814814f), sf::Vector2f(218.37096296296295f,433.86785185185187f), sf::Vector2f(212.736f,437.272f), sf::Vector2f(207.03703703703707f,439.4814814814814f), sf::Vector2f(201.4002962962963f,440.3931851851852f), sf::Vector2f(195.95199999999994f,439.904f), sf::Vector2f(190.81837037037042f,437.91081481481484f), sf::Vector2f(186.12562962962966f,434.3105185185185f), sf::Vector2f(182.0f,429.0f)};

    std::vector<sf::Vector2f> path_m1(x, x + 90);
    path_m1 = Utils::getPathFractionned(path_m1);
    model1.setPointBehavior(path_m1);

    model1.addWeapon(new Generator1(context->bullet,0.3f,1));

    ShipEnemy model2 = ShipEnemy(30);
    model2.setTexture(*textures.getTexture("ressources/img_ship/ship3.png"),true);
    //model2.getSprite().setColor(sf::Color::White);
    model2.setVyBehavior(BehaviorAstract::inverse);
    model2.addWeapon(new Generator2(context->bullet,1.5f,5,32));
    model2.linkSpriteRotation();

    ShipEnemy model3 = ShipEnemy(100);
    model3.setTexture(*textures.getTexture("ressources/img_ship/ship5.png"),true);
    model3.setVy(20.f);
    model3.setPosition(winWidth/2.f,100.f);
    model3.addWeapon(new Generator4(context->bullet));

    ShipEnemy model4 = ShipEnemy(100);
    model4.setTexture(*textures.getTexture("ressources/img_ship/ship4.png"),true);
    model4.setVy(20.f);
    model4.setPosition(winWidth/2.f,100.f);
    model4.addWeapon(new Generator4(context->bullet));

    unsigned int id_m1 = mission->storeModel(model1);
    //unsigned int id_m2 = game->storeModel(model2);
    unsigned int id_m3 = mission->storeModel(model3);
    //unsigned int id_m4 = game->storeModel(model4);

    // programmation

    float posx,time=begin;
    {
        const int nb = 5;
        float timespace = 5.f;

        for(int i=0;i<nb;i++){
            posx = 100.f+(winWidth-400.f)*i/nb;
            time += timespace;
            mission->addToProgrammation(id_m1,time,sf::Vector2f(posx,50.f));
        }
    }

    time += 10.f;
    mission->addToProgrammation(id_m3,time);

    /*time += 10.f;
    model2.setRotation(-30.f);
    unsigned int id_m2[2];
    id_m2[0] = game->storeModel(model2);
    model2.setRotation(30.f);
    id_m2[1] = game->storeModel(model2);

    for(int i=0;i<2;i++){
        time += 1.f;
        posx = 50.f+10.f*i;
        game->addToProgrammation(id_m2[0],time,sf::Vector2f(posx,150.f));
        posx = winWidth-posx;
        game->addToProgrammation(id_m2[1],time,sf::Vector2f(posx,150.f));
    }

    */
    mission->sortProgrammation();

        // image showing "mission 1"
    splash_tex.loadFromFile("ressources/img2/m1splash.png");
    splash1 = sf::Sprite(splash_tex,sf::IntRect(0,0,380,120));
    splash2 = sf::Sprite(splash_tex,sf::IntRect(0,120,380,240));
    splash1.setColor(sf::Color::Transparent);
    splash2.setColor(sf::Color::Transparent);
    splash1.setPosition((winWidth-splash1.getLocalBounds().width)/2,
                        (context->window->getSize().y-splash1.getLocalBounds().height)/2);
    splash2.setPosition((winWidth-splash2.getLocalBounds().width)/2,
                        (context->window->getSize().y-splash1.getLocalBounds().height)/2);
}

void MissionState1_1::update(float)
{
    float elapsed = mission->getElapsedTime();
    if(elapsed < 5.f){
        if(elapsed < d2+a2 && elapsed > a2){
            int alpha = 255*(float)((elapsed-a2)/d2);
            splash2.setColor(sf::Color(255,255,255,alpha));
        }
        if(elapsed < d1+a1 && elapsed > a1){
            int alpha = 255*(elapsed-a1)/d1;
            splash1.setColor(sf::Color(255,255,255,alpha));
        }
        mission->getContext().layer_game->draw(splash1);
        mission->getContext().layer_game->draw(splash2);
    }
}

// ----------------------------------------------------------------------------
MissionState1_2::MissionState1_2(Mission* m, MissionState* n):
    MissionState(m,n)
{
    mode = DEATHMATCH;
}

void MissionState1_2::init()
{
    //MissionContext const& context = mission->getContext();
    const float winWidth = *context->winWidth;

    // models
    ShipEnemy model3 = ShipEnemy(500);
    model3.setTexture(*textures.getTexture("ressources/img_ship/ship5.png"),true);
    int temp_size = 0.f*model3.getSprite().getGlobalBounds().width/2.f;
    model3.setVy(20.f);
    model3.setPosition(winWidth*0.4f-temp_size,100.f);
    model3.addWeapon(new Generator4(context->bullet,1.5f, 3, 6, 3, 0.f));
    unsigned int id_m3 = mission->storeModel(model3);


    model3.setVy(20.f);
    model3.setPosition(winWidth*0.6f-temp_size,100.f);
    model3.addWeapon(new Generator4(context->bullet,1.5f, 3, 6, 3, 0.f));
    unsigned int id_m3_bis = mission->storeModel(model3);


    ShipEnemy bossm1 = ShipEnemy(1500);
    bossm1.setTexture(*textures.getTexture("ressources/img_ship/ship4.png"),true);
    bossm1.setPosition( (winWidth-bossm1.getSprite().getGlobalBounds().width)/2.f,
                       100.f);
    bossm1.setVxBehavior(BehaviorAstract::cos200f1);
    bossm1.addWeapon(new Generator5(context->bullet,0.19f, 3.f, 5.f, 0.02f, 100.f, 0.1f, 0.f));
    unsigned int id_bossm1 = mission->storeModel(bossm1);


    mission->addToProgrammation(id_m3,0.f);
    mission->addToProgrammation(id_m3_bis,0.f);
    mission->addToProgrammation(id_bossm1,1.f);

    mission->sortProgrammation();
    initialLives=model3.getLives();

    lifebar.centerOnX(winWidth);
}

void MissionState1_2::update(float)
{
    //MissionContext const& context = mission->getContext();
    if(context->game->getRemainingEnnemyLife() != 0){
        /*lifebar.setScale(271.f*context->game->getRemainingEnnemyLife()/
                         context->game->getRemainingEnnemyLifeMax(),1.f);
        context->layer_game->draw(lifebar);
        context->layer_game->draw(lifebarBorder);*/
        lifebar.update((float)context->game->getRemainingEnnemyLife()/
                         context->game->getRemainingEnnemyLifeMax());
        context->layer_game->draw(lifebar);
    }
}

