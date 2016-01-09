#include "../include/MissionManager.h"

std::ostream& operator<<(std::ostream & os,const MissionFileState &m){
    os<<"m"<<m.id<<std::endl<<static_cast<int>(m.state)<<std::endl;
    return os;
}

//---

Mission* MissionManager::createMission(unsigned int id, Game* game){
    if(id > 0 && getMissionState(id) == false)
        return 0;

    switch(id){
        case 0:
            return new Mission1(game);
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            return new Mission1(game);
            break;
        default:;
    }
    return 0;
}

MissionManager::MissionManager()
{

}

bool MissionManager::getMissionState(unsigned int id) const
{
    if(id > mission.size())
        return false;
    else
        return mission[id].state;
}

void MissionManager::unlock(unsigned int id)
{
    mission[id].state = true;
}

std::string MissionManager::getMissionName(unsigned int id) const
{
    if(id > mission.size())
        return "<invalid mission>";
    else
        return ttos(id+1);
}

void MissionManager::save(){
    std::fstream playerData("data.txt",std::ios_base::out);
    std::string s = "";
    s += "valid\n";
    s += "m0\n1\n";
    playerData<<s.c_str();
    for(int i=1;i<NB_MISSION;i++){
        playerData<<mission[i];
        /*s += "m"+ttos(i)+'\n';
        mission[i].state ? s+='1':s+='0';
        s += '\n';*/
    }
}

unsigned int MissionManager::size() const { return mission.size();}

void MissionManager::load()
{
    /* Note the progress file is written this way :
    valid   < --- a const string used to check at the begining if the file
            is valid
    m1      < --- no mission
    1       < --- 1 if mission unlocked else 0
    m2
    0
    ...*/

    mission.clear();
    bool ok = false;
    MissionFileState temp = MissionFileState();
    std::string s;
    {
        std::fstream playerData("data.txt",std::ios_base::in|std::ios_base::out);
        int mode = 0;
        while(playerData>>s){
            if(!ok){
                if(s == "valid"){
                    ok = true;
                }
            }else{
                // mode = 0 -> mission number
                if(mode == 0){
                    if(s.size()>=2 && s[0] == 'm'){
                        s = s.substr(0)[1];
                        temp.id = stot<int>(s);
                    }else{
                        ok = false;
                        break;
                    }
                // mode = 1 -> tells if the mission is unlocked or not
                }else if(mode == 1){
                    if(s.size()==1){
                        temp.state = stot<int>(s);
                        mission.push_back(temp);
                    }else{
                        ok = false;
                        break;
                    }
                    mode = -1;
                }
                mode++;
            }
        }
        // at the end if mode != 0
        // it means that a state (mission accessible or not) is missing
        if((int)mission.size() < NB_MISSION || mode != 0){
            ok = false;
        }
    }
    {
        if(!ok){
            std::fstream playerData("data.txt",std::ios_base::out);
            s = "";
            s += "valid\n";
            s += "m0\n1\n";
            mission.push_back(MissionFileState(0,1));
            for(int i=1;i<NB_MISSION;i++){
                s += "m"+ttos(i)+'\n';
                s += "0\n";
                mission.push_back(MissionFileState(i,0));
            }
            playerData<<s.c_str();

        }
    }
}
