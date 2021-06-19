#include<bits/stdc++.h>
using namespace std;

class Creature;

class Profession{

     public:
    int strengthBonus,dexterityBonus,healthBonus,coolDown;
    Profession *newProfession;
    Profession()
    {

    }
    Profession(int strengthBonus,int dexterityBonus,int healthBonus,int coolDown)
    {
        this->strengthBonus = strengthBonus;
        this->dexterityBonus = dexterityBonus;
        this->healthBonus = healthBonus;
        this->coolDown = coolDown;
    }

    virtual void professionalAbility(Creature *target1, Creature *target2)
    {

    }

};



class Race{
    public:
    int baseStrength,baseDexterity,baseHealth,coolDown;
    Race *newRace;
    Race()
    {

    }
    Race(int baseStrength,int baseDexterity,int baseHealth,int coolDown)
    {
        
        this->baseStrength = baseStrength;
        this->baseDexterity = baseDexterity;
        this->baseHealth = baseHealth;
        this->coolDown=coolDown;
    }

    virtual bool racialAbility(Creature *target)
    {
        return false;
    }
};


class Creature{
    public:
    int strength,dexterity,health,maxHealth;
    Race *race;
    Profession *profession;
    
    Creature(Race *race,Profession *profession)
    {
      
        this->race = race;
        this->profession = profession;
        this->strength = race->newRace->baseStrength + profession->newProfession->strengthBonus;
        this->dexterity = race->newRace->baseDexterity + profession->newProfession->dexterityBonus;
        this->health = race->newRace->baseHealth + profession->newProfession->healthBonus;
        this->maxHealth = race->newRace->baseHealth + profession->newProfession->healthBonus;
    }

    void coolDownTimer(Creature *target)
    {
        target->race->newRace->coolDown = max(target->race->newRace->coolDown-1,0);
        target->profession->newProfession->coolDown = max( target->profession->newProfession->coolDown-1,0);
    }

    void action(Creature *target )
    {
        coolDownTimer(this);
        coolDownTimer(target);
      
        if(this->race->newRace->coolDown==0)
        {
            
            if( ! this->race->racialAbility(this) )
            {
                this->race->racialAbility(target);
            }
        }
        else if(this->profession->newProfession->coolDown==0)
        {
            this->profession->professionalAbility(this,target);
        }
        else{
            target->health-=(max(this->dexterity,this->strength));
        }
    }   
};



class Troll : public Race
{
    public:
    
    Troll()
    {
        newRace = new Race(10,2,200,0);
    }

    bool racialAbility(Creature *target)
    {
        
         target->health = (target->health+40,target->maxHealth);
         target->race->newRace->coolDown = 3;
         return true;
    }
 
};



class Sprite :public Race
{
    public:
    
    Sprite()
    {
        newRace = new Race(2,10,150,0);
    }
    bool racialAbility(Creature *target)
    {
        if(this!=target->race)
        {
            target->race->newRace->coolDown*=2;
            target->profession->newProfession->coolDown*=2;
            this->newRace->coolDown=4;
            return true;
        }
        else{
            return false;
        }
        return true;
    }
};



class Ghoul :public Race{
    public:
    Ghoul()
    {
        newRace = new Race(6,6,150,0);
    }
    bool racialAbility(Creature *target)
    {
        if(this!=target->race)
        {
            target->dexterity = max(target->dexterity-1,1);
            target->strength = max(target->health-1,1);
            this->newRace->coolDown = 4;
        }
        return false;
    }
};





class Galidator :public Profession
{
    public:
    
    Galidator()
    {
        newProfession = new Profession(5,5,150,0);
    }
    void professionalAbility(Creature *target1,Creature *target2)
    {
       
        target2->health -=(target1->strength + target1->dexterity);
        target1->profession->newProfession->coolDown=3; 
    }
};

class Thug : public Profession
{
    public:
    
    Thug()
    {
        newProfession = new  Profession(2,10,80,0);
    }
     void professionalAbility(Creature *target1,Creature *target2)
    {
        target2->health-=(2*(target1->dexterity));
        target1->profession->newProfession->coolDown=4; 
    }
};

class Brute : public Profession
{
    public:
    
    Brute()
    {
        newProfession = new Profession(10,2,150,0);
    }
     void professionalAbility(Creature *target1,Creature *target2)
    {
        target2->health -=(2*(target1->strength));
        target1->profession->newProfession->coolDown=4; 
    }
};






void printStatus(Creature *c)
{
    cout<<"Player current health= "<<c->health<<"\n";
    cout<<"Player current dexterity is = "<<c->dexterity<<"\n";
    cout<<"Player current strength is ="<< c->strength<<"\n";
}


Race* chooseRace()
{
    cout<<"Enter the choice for Race\n";
    cout<<"Enter 1 for Troll\n Enter 2 for sprite\n Enter 3 for ghoul\n";
    int choice;
    while(1)
    {
        cin>>choice;
        switch (choice)
        {
            case 1:
                    {Race *obj = new Troll();
                    return obj;
                    }
            case 2:
                    {Race *obj = new Sprite();
                    return obj;}
            case 3:
                    {Race *obj = new Ghoul();
                    return obj;}
            default:
                    {cout<<"Wrong Choice Enter again\n";
                    break;}
        }
    }
  
    return 0;
}

Profession* chooseProfession()
{
      cout<<"Enter the choice for Race\n";
    cout<<"Enter 1 for Galidator\n Enter 2 for thug\n Enter 3 for brute\n";
    int choice;
    while(1)
    {
        cin>>choice;
        switch (choice)
        {
            case 1:
                    {Profession *obj = new Galidator();
                    return obj;}
            case 2:
                    {Profession *obj = new Thug();
                    return obj;}
            case 3:
                    {Profession *obj = new Brute();
                    return obj;}
            default:
                    {cout<<"Wrong Choice Enter again\n";
                    break;}
        }
    }
  
}

Creature *createCreature()
{

    Race *obj1 = chooseRace();
    Profession *obj2 = chooseProfession();
    Creature *oponent = new Creature(obj1,obj2);
    return oponent;
    
}


int main()
{
    Creature *oponent1,*oponent2;
    oponent1 = createCreature();
    oponent2 = createCreature();
    int cnt=0;
   
    while (cnt<10000 and oponent1->health>0 and oponent2->health>0)
    {
        
        if(cnt%2==0)
        {
            oponent1->action(oponent2);
        }
        else{
            oponent2->action(oponent1);
        }
        cout<<"----------------------------------------------\n";
        cout<<"\n Oponent1\n";
        printStatus(oponent1);
        cout<<"------\n";
        cout<<"\n Oponent2 \n";
        printStatus(oponent2);
  

        cnt+=1;
    }

    if(cnt==10000)
    {
        cout<<"Both players are of same strength so match is a draw\n";
    }
    
    return 0;
}