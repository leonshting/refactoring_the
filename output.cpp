//
// Created by leonsht on 3/10/16.
//

#include "output.h"

output::output(VectorXd &answer, settings &S, init_data &it): Answer(answer), Settings(S), initData(it)
{
    cAnswer = cAnswer_fromD(Answer);
    fin_ISREADY = false;
    partData = nullptr;
}

output::output(VectorXd &answer, settings &S, init_data &it, init_data &pt):Answer(answer), Settings(S), initData(it) {
    cAnswer = cAnswer_fromD(Answer);
    fin_ISREADY = false;
    partData = new init_data(pt);
}


VectorXcd output::cAnswer_fromD(VectorXd &answer) {
    int csize = int(answer.rows()/2);
    VectorXcd ret(csize);
    for(int i = 0 ; i < csize; i++)
       ret(i) = cd(answer(i), answer(csize+i));
    return ret;
}

void output::make_polynoms(sub_pol polPHI, sub_pol polXI) {
    map<string, data_points<data_point_with_azimuth>>::iterator i;
    for(i = initData.data_points_collection.begin(); i!=initData.data_points_collection.end(); ++i)
    {
        tag_to_Dpolynom.insert({i->second.tag, make_Dpolynom(i->second, polPHI, polXI)});
        tag_to_Ppolynom.insert({i->second.tag, make_Ppolynom(i->second, polPHI, polXI)});
    }
}



string output::make_Dpolynom(data_points<data_point_with_azimuth> &subj, sub_pol polPHI, sub_pol polXI) {
    stringstream ret;
    int ORDER = (Settings.ORDERS.find(subj.tag)!=Settings.ORDERS.end())?Settings.ORDERS.at(subj.tag):Settings.default_order;
    for(int i = 0; i <= ORDER; i++)
    {
        ret << polPHI(i, cAnswer(Settings.get_start(subj.tag) + i), Settings.get_zero(subj.tag),
                      Settings.get_pole(subj.tag), Settings.get_pole_x(subj.tag), true);
            ret << " + ";
        ret << polXI(i, cAnswer(cAnswer.rows()/2 + Settings.get_start(subj.tag) + i), Settings.get_zero(subj.tag),
                     Settings.get_pole(subj.tag), Settings.get_pole_x(subj.tag), true);
        if(i != ORDER)
            ret << " + ";
    }
    return ret.str();
}

string output::get_polynom(string &key) {
    auto search = tag_to_Dpolynom.find(key);
    return search->second;
}

string output::get_formatted_output() {
    stringstream ret;
    if(tag_to_Dpolynom.empty() || tag_to_Ppolynom.empty())
    {
        throw POLYNOMS_ARENT_READY;
    }
    else
    {
        map<string, data_points<data_point_with_azimuth>>::iterator i;
        for (i = initData.data_points_collection.begin(); i != initData.data_points_collection.end(); ++i) {
            ret << i->second.tag << ": D: " << tag_to_Dpolynom.at(i->second.tag) << endl;
            ret <<"P: " << tag_to_Ppolynom.at(i->second.tag) << endl;
        }
    }

    if(fin_ISREADY)
        ret << "Multiplicative constant: " << finAnswer(0) << endl << "Additive constant:" << finAnswer(1);
    return ret.str();
}

string output::make_Ppolynom(data_points<data_point_with_azimuth> &subj, sub_pol polPHI, sub_pol polXI) {
    stringstream ret;
    int ORDER = (Settings.ORDERS.find(subj.tag)!=Settings.ORDERS.end())?Settings.ORDERS.at(subj.tag):Settings.default_order;
    for(int i = 0; i <= ORDER; i++)
    {
        ret << polXI(i, cAnswer(cAnswer.rows()/2 + Settings.get_start(subj.tag) + i), Settings.get_zero(subj.tag),
                     Settings.get_pole(subj.tag), Settings.get_pole_x(subj.tag), false);
        if(i != ORDER)
            ret << " + ";
    }
    return ret.str();
}

cd output::getD(cd z, string &tag) {
    int ORDER = (Settings.ORDERS.find(tag)!=Settings.ORDERS.end())?Settings.ORDERS.at(tag):Settings.default_order;
    cd ret;
    for(int i = 0; i <= ORDER; i++)
    {
        ret += cAnswer(Settings.get_start(tag) + i) * powZ_POLE(z, i, Settings.get_zero(tag), Settings.get_pole(tag), Settings.get_pole_x(tag));
        ret += cAnswer(cAnswer.rows()/2 + Settings.get_start(tag) + i) * powZ_conj_POLE(z, i, Settings.get_zero(tag), Settings.get_pole(tag), Settings.get_pole_x(tag));
    }
    return ret;
}

cd output::getP(cd z, string &tag) {
    int ORDER = (Settings.ORDERS.find(tag)!=Settings.ORDERS.end())?Settings.ORDERS.at(tag):Settings.default_order;
    cd ret;
    for(int i = 0; i <= ORDER; i++)
        ret += cAnswer(cAnswer.rows()/2 + Settings.get_start(tag) + i) * powZ_integrated(z, i, Settings.get_zero(tag), Settings.get_pole(tag), Settings.get_pole_x(tag));
    return ret;
}

cd output::get_full(cd z, double azimuth, string &key) {
    cd P = getP(z, key);
    cd D = getD(z, key);
    return cd(2*P.real(), 0.0) + D * exp(cd(0.0, -2.0 * azimuth));
}

double output::get_normal(cd z, double azimuth, string &tag) {
    return finAnswer(0) * get_full(z, azimuth, tag).real() + finAnswer(1);
}

double output::get_shear(cd z, double azimuth, string &tag) {
    return finAnswer(0) * get_full(z, azimuth, tag).imag();
}


double output::get_disrepancy_over_principals() {
    if(!tag_to_Dpolynom.empty() && !tag_to_Ppolynom.empty())
    {
        map<string, data_points<data_point_with_azimuth>>::iterator i;
        vector<data_point_with_azimuth>::iterator j;
        double disrepancy = 0.0;
        for(i = initData.data_points_collection.begin(); i != initData.data_points_collection.end(); ++i)
        {
            for(j = (*i).second.data.begin(); j != (*i).second.data.end(); ++j)
            {
                cd D = getD((*j).complex_coordinates, (*i).second.tag);
                double azimuth = arg(D);
                double tmp = abs(fromPI_to_PI(azimuth + fromPI_to_PI(2 * (*j).Azimuth)));
                disrepancy += tmp;
            }
        }
        return disrepancy/initData.total_num_of_points/2;
    }
    else
        throw(POLYNOMS_ARENT_READY);
}


void output::update_part_data(init_data &pD) {
    delete partData;
    partData = new init_data(pD);
}

double output::get_orientation(cd z, string &tag) {
    cd D = getD(z, tag);
    return fromPI_to_PI(arg(D))/2;
}





