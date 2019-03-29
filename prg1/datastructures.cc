// Datastructures.cc

#include "datastructures.hh"
#include <vector>
#include <random>
#include <iostream>
#include <cmath>
#include <stack>
#include <algorithm>


std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    beaconlist_ = {};
}

Datastructures::~Datastructures()
{
    clear_beacons();
}

int Datastructures::beacon_count()
{
    // Replace this with your implementation
    return int(beaconlist_.size());
}

void Datastructures::clear_beacons()
{
    // Replace this with your implementation
    for(int i=0;i<(beaconlist_.size());i++)
    {
        delete beaconlist_.at(i);
    }
    beaconlist_.clear();
}


std::vector<BeaconID> Datastructures::all_beacons()
{
    for(int i=0;i<(beaconlist_.size());i++)
    {
        IDlist_.push_back(beaconlist_.at(i)->id);
    };
    // Replace this with your implementation
    return IDlist_;
}

bool Datastructures::add_beacon(BeaconID id/*id*/, const std::string& name/*name*/, Coord xy/*xy*/, Color color/*color*/)
{
    // Replace this with your implementation
    auto it = std::find(IDlist_.begin(), IDlist_.end(), id);
    if(it== IDlist_.end())
    {
        BeaconData* p = new BeaconData;
        p->id = id;
    //    p->master =NULL ;
        p->name = name;
        p->xy = xy;
        p->color = color;
        p->brightness_=3*color.r+6*color.g+color.b;
        beaconlist_.push_back(p);
        IDlist_.push_back(id);
        return true;
    }
    return false;
}

std::string Datastructures::get_name(BeaconID id/*id*/)
{
    for(int i=0;i<(beaconlist_.size());i++)
    {
        if(beaconlist_.at(i)->id==id) return beaconlist_.at(i)->name;
    }
    return NO_NAME;
}

Coord Datastructures::get_coordinates(BeaconID id/*id*/)
{
    // Replace; this with your implementation
    for(int i=0;i<(beaconlist_.size());i++)
    {
        if(beaconlist_.at(i)->id==id) return beaconlist_.at(i)->xy;
    }
    return NO_COORD;
}

Color Datastructures::get_color(BeaconID id/*id*/)
{
    for(int i=0;i<(beaconlist_.size());i++)
    {
        if(beaconlist_.at(i)->id==id) return beaconlist_.at(i)->color;
    }
    return NO_COLOR;
}

std::vector<BeaconID> Datastructures::beacons_alphabetically()
{
    std::sort(beaconlist_.begin(), beaconlist_.end(), [](BeaconData* p, BeaconData* q)
    {return p->name < q->name;});
    std::vector<BeaconID> allbeacons;
    for(int i=0;i< (beaconlist_.size());i++)
    {
        allbeacons.push_back(beaconlist_.at(i)->id);
//        namelist_.push_back(beaconlist_.at(i)->name);
    };
    return allbeacons;
}

std::vector<BeaconID> Datastructures::beacons_brightness_increasing()
{
    std::sort(beaconlist_.begin(), beaconlist_.end(), [](BeaconData* p, BeaconData* q)
    {return p->brightness_ < q->brightness_;});
    for(int i=0;i<(beaconlist_.size());i++)
    {
        brightness_increasing.push_back(beaconlist_.at(i)->id);
    };
    return brightness_increasing;
}

BeaconID Datastructures::min_brightness()
{
    if (brightness_increasing.size()) return brightness_increasing[0];
    return NO_ID;
}

BeaconID Datastructures::max_brightness()
{
    if (brightness_increasing.begin() != brightness_increasing.end()) return brightness_increasing[-1];
    return NO_ID;
}

std::vector<BeaconID> Datastructures::find_beacons(std::string const& name/*name*/)
{
    // Replace this with your implementation
    std::vector<BeaconID> IDs;
    for(int i=0;i<beaconlist_.size();i++)
    {
        if(beaconlist_.at(i)->name==name) IDs.push_back(beaconlist_.at(i)->id);
    }
    if (IDs.begin() != IDs.end()) return IDs;
    else return {NO_ID};
}

bool Datastructures::change_beacon_name(BeaconID id/*id*/, const std::string& newname/*newname*/)
{
    // Replace this with your implementation
    for(int i=0;i<(beaconlist_.size());i++)
    {
        if(beaconlist_.at(i)->id==id) beaconlist_.at(i)->name = newname;
        return true;
    }
    return false;
}

bool Datastructures::change_beacon_color(BeaconID id/*id*/, Color newcolor/*newcolor*/)
{
    for(int i=0;i<(beaconlist_.size());i++)
    {
        if(beaconlist_.at(i)->id==id) beaconlist_.at(i)->color = newcolor;
        return true;
    }
    return false;
}

bool Datastructures::add_lightbeam(BeaconID sourceid/*sourceid*/, BeaconID targetid/*targetid*/)
{
    auto ind = std::find(IDlist_.begin(),IDlist_.end(), sourceid);
    BeaconData *p = beaconlist_.at(ind-IDlist_.begin());
    if ((p->vassal.size() == 0) && (ind != IDlist_.end()))
    {
        p->vassal = targetid;
        beaconlist_.at(ind-IDlist_.begin()) = p;
        auto id = std::find(IDlist_.begin(),IDlist_.end(), targetid);
        beaconlist_.at(ind-IDlist_.begin())->master.push_back(sourceid);
        beaconlist_.at(ind-IDlist_.begin())->color.r =  (beaconlist_.at(id-IDlist_.begin())->color.r+p->color.r)/2;
        beaconlist_.at(ind-IDlist_.begin())->color.g =  (beaconlist_.at(id-IDlist_.begin())->color.g+p->color.g)/2;
        beaconlist_.at(ind-IDlist_.begin())->color.b =  (beaconlist_.at(id-IDlist_.begin())->color.b+p->color.b)/2;
        beaconlist_.at(ind-IDlist_.begin())->dist = p->dist +1;
        return true;
    }
    // Replace this with your implementation
    return false;
}

std::vector<BeaconID> Datastructures::get_lightsources(BeaconID id/*id*/)
{
    auto ind = std::find(IDlist_.begin(),IDlist_.end(), id);
    BeaconData *p = beaconlist_.at(ind-IDlist_.begin());
    if((p->master.size() != 0) && (ind != IDlist_.end()))
    {
        return p->master;
    }
    return {NO_ID};
    //return {NO_ID}; // Replace with actual implementation
}

std::vector<BeaconID> Datastructures::path_outbeam(BeaconID id/*id*/)
{
    auto ind = std::find(IDlist_.begin(), IDlist_.end(), id);
    std::vector<BeaconID> q;
    if(ind!= IDlist_.end())
    {
        BeaconData *p;
        p = beaconlist_.at(ind-IDlist_.begin());
        while(p->vassal.size() != 0)
        {
            q.push_back(p->vassal);
            auto ind = std::find(IDlist_.begin(),IDlist_.end(), p->vassal);
            if(ind!= IDlist_.end()) p = beaconlist_.at(ind-IDlist_.begin());
        }
        return q;
    }
    return {NO_ID};
}

bool Datastructures::remove_beacon(BeaconID id/*id*/)
{
    // Replace this with your implementation
    auto ind = std::find(IDlist_.begin(),IDlist_.end(), id);
    if(ind != IDlist_.end())
    {
        beaconlist_.at(ind-IDlist_.begin())=beaconlist_.at(ind-IDlist_.begin()+1);
        int count = IDlist_.size()-(ind-IDlist_.begin())-1;
        while(count>0)
        {
            ind ++;
            beaconlist_.at(ind-IDlist_.begin())=beaconlist_.at(ind-IDlist_.begin()+1);
            count --;
        }
        delete beaconlist_[-1];
        return true;
    }
    return false;
}

std::vector<BeaconID> Datastructures::path_inbeam_longest(BeaconID id/*id*/)
{
    auto ind = std::find(IDlist_.begin(),IDlist_.end(), id);
    if(ind!=IDlist_.end())
    {
        std::vector<BeaconID> *q;
        std::vector<BeaconID> shortest;
        BeaconData *p;
        p = beaconlist_.at(ind-IDlist_.begin());
        int count;
        count = p->master.end()-p->master.begin();
        while (count > 0)
        {
            q[count-1].push_back(p->id);
            auto ind = std:: find(IDlist_.begin(),IDlist_.end(), (p->master)[count-1]);
            if (ind != IDlist_.end())
            {
                q[count-1].push_back(p->master[count-1]);
            }
            shortest = q[count-1];
            int c = count -1;
            while(c > 0)
            {
                auto ind2 = std:: find(IDlist_.begin(),IDlist_.end(), (p->master)[c-1]);
                if (ind2 != IDlist_.end())
                {
                    c--;
                    q[count-1].push_back(p->master[count-1]);
                    if(q[count+1].end()-q[count+1].begin() >count) shortest = q[count];
                    if (c==0) break;
                }
            }

            count --;
         }
        return shortest;

    }
    return {NO_ID};
}

Color Datastructures::total_color(BeaconID id/*id*/)
{
    auto ind = std::find(IDlist_.begin(),IDlist_.end(), id);
    int count = 0;
    if(ind != IDlist_.end())
    {   BeaconData *p;
        p = beaconlist_.at(ind-IDlist_.begin());
        Color totalcolor;
        totalcolor = p->color;
        while(p->vassal.size() != 0)
        {
            auto ind = std::find(IDlist_.begin(),IDlist_.end(), p->vassal);
            if(ind!=IDlist_.end())
            {
                p = beaconlist_.at(ind-IDlist_.begin());
                totalcolor.r = totalcolor.r + p->color.r;
                totalcolor.r = totalcolor.r + p->color.r;
                totalcolor.r = totalcolor.r + p->color.r;
            }
            count ++;
        }
        totalcolor.r = totalcolor.r/(count--);
        totalcolor.g = totalcolor.g/(count--);
        totalcolor.b = totalcolor.b/(count--);
        return totalcolor;
    }
    return {NO_COLOR};
}

//void Datastructure::quick_sort_name(std::<BeaconData*>& beaclonlist, int i, int j)
//{
//    BeaconData *tmp = beaconlist_.at((left+right)/2);
//    int i = left, j = right;
//    int pivot = tmp->name;
//    while(i<=j)
//    {
//        while(beaconlist_.at(i)->name < pivot) i++;
//        while(beaconlist_.at(j)->name > pivot) j--;
//        if (i <=j)
//        {
//            tmp = beaconlist_.at(i);
//            beaconlist_.at(i) = beaconlist_.at(j);
//            beaconlist_.at(i) =tmp;
//            i++;
//            j--;
//        }
//    }
//    if(left<j) quick_sort_name(beaconlist, left, j);
//    if(i<right) quick_sort_name(beaconlist, i, tight);
//}

//void Datastructure::quick_sort_brightness(std::<BeaconData*>& beaclonlist, int i, int j)
//{
//    BeaconData *tmp = beaconlist_.at((left+right)/2);
//    int i = left, j = right;
//    int pivot = tmp->brightness;
//    while(i<=j)
//    {
//        while(beaconlist_.at(i)->brightness < pivot) i++;
//        while(beaconlist_.at(j)->brightness > pivot) j--;
//        if (i <=j)
//        {
//            tmp = beaconlist_.at(i);
//            beaconlist_.at(i) = beaconlist_.at(j);
//            beaconlist_.at(i) =tmp;
//            i++;
//            j--;
//        }
//    }
//    if(left<j) quick_sort_brightnesse(beaconlist, left, j);
//    if(i<right) quick_sort_brightness(beaconlist, i, tight);
//}
