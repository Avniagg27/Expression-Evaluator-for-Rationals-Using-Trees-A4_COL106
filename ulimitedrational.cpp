/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

UnlimitedRational::UnlimitedRational(){
    p = new UnlimitedInt("1");
    q = new UnlimitedInt("1");
}
UnlimitedInt* gcd(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* temp1 = new UnlimitedInt(i1->to_string()); // Create a copy
    UnlimitedInt* temp2 = new UnlimitedInt(i2->to_string()); // Create a copy

    if(temp1->to_string() == "1" || temp2->to_string() == "1"){
        delete temp2;
        return new UnlimitedInt("1");
    }

    while(temp2->to_string() != "0"){
        UnlimitedInt* t = new UnlimitedInt(temp1->to_string());
        delete temp1; // Delete the old value before assigning the new one
        temp1 = new UnlimitedInt(temp2->to_string());
        temp2 = UnlimitedInt::mod(t, temp2);
        delete t;
    }

    delete temp2;
    return temp1;
}

UnlimitedRational::UnlimitedRational(UnlimitedInt* num, UnlimitedInt* den){
    if(den->get_sign() == 0){
        p = new UnlimitedInt("0");
        q = new UnlimitedInt("0");
        return;
    }
    else if(num->get_sign()== 0){
        p = new UnlimitedInt("0");
        q = new UnlimitedInt("1");
        return;
    }
    
    else{
        UnlimitedInt* y;
        y = new UnlimitedInt(num->get_array(),num->get_capacity(),1,num->get_size());
        UnlimitedInt* z;
        z = new UnlimitedInt(den->get_array(),den->get_capacity(),1,den->get_size());
        UnlimitedInt* x;
        x = gcd(y,z);
        p = UnlimitedInt::div(y, x);
        q = UnlimitedInt::div(z, x);
        delete x;
        delete y;
        delete z;
    }
}

UnlimitedRational::~UnlimitedRational(){
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational::get_p(){
    return p;
}

UnlimitedInt* UnlimitedRational::get_q(){
    return q;
}

string UnlimitedRational::get_p_str(){
    return p->to_string();
}

string UnlimitedRational::get_q_str(){
    return q->to_string();
}

string UnlimitedRational::get_frac_str(){
    if(get_q_str() == "0"){
        return "0/0";
    }
    else if(get_p_str() == "0"){
        return "0/" + q->to_string();
    }
    return p->to_string() + "/" + q->to_string();
}

UnlimitedRational* UnlimitedRational::add(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* x = new UnlimitedInt("0");
    UnlimitedInt* y = new UnlimitedInt("0");
    UnlimitedRational* res = new UnlimitedRational(x,y);
    if(i1->get_frac_str()=="0/0" || i2->get_frac_str() == "0/0"){
        return res;
    }
    delete x;
    delete y;

    UnlimitedInt* a = new UnlimitedInt(i1->get_p_str());
    UnlimitedInt* b = new UnlimitedInt(i1->get_q_str());
    UnlimitedInt* c = new UnlimitedInt(i2->get_p_str());
    UnlimitedInt* d = new UnlimitedInt(i2->get_q_str());

    UnlimitedInt* p1q2 = UnlimitedInt::mul(a,d);
    UnlimitedInt* p2q1 = UnlimitedInt::mul(c,b);
    UnlimitedInt* q1q2 = UnlimitedInt::mul(d,b);
    UnlimitedInt* m = UnlimitedInt::add(p1q2,p2q1);
    UnlimitedRational* res1 = new UnlimitedRational(m,q1q2);
    delete p1q2;
    delete p2q1;
    delete q1q2;
    delete a;
    delete b;
    delete c;
    delete d;
    delete res;

    return res1;
}

UnlimitedRational* UnlimitedRational::sub(UnlimitedRational* i1, UnlimitedRational* i2){
    
    UnlimitedInt* x = new UnlimitedInt("0");
    UnlimitedInt* y = new UnlimitedInt("0");
    UnlimitedRational* res = new UnlimitedRational(x,y);
    if(i1->get_frac_str() == "0/0" || i2->get_frac_str() == "0/0"){
        return res;
    }
    delete x;
    delete y;

    UnlimitedInt* a = new UnlimitedInt(i1->get_p_str());
    UnlimitedInt* b = new UnlimitedInt(i1->get_q_str());
    UnlimitedInt* c = new UnlimitedInt(i2->get_p_str());
    UnlimitedInt* d = new UnlimitedInt(i2->get_q_str());

    UnlimitedInt* p1q2 = UnlimitedInt::mul(a,d);
    UnlimitedInt* p2q1 = UnlimitedInt::mul(c,b);
    UnlimitedInt* q1q2 = UnlimitedInt::mul(d,b);
    UnlimitedInt* m = UnlimitedInt::sub(p1q2,p2q1);
    UnlimitedRational* res1 = new UnlimitedRational(m,q1q2);
    delete p1q2;
    delete p2q1;
    delete q1q2;
    delete a;
    delete b;
    delete c;
    delete d;
    delete res;

    return res1;
}

UnlimitedRational* UnlimitedRational::mul(UnlimitedRational* i1, UnlimitedRational* i2){

    UnlimitedInt* x = new UnlimitedInt("0");
    UnlimitedInt* y = new UnlimitedInt("0");
    UnlimitedRational* res = new UnlimitedRational(x,y);
    if(i1->get_frac_str() == "0/0" || i2->get_frac_str() == "0/0"){
        return res;
    }
    delete x;
    delete y;

    UnlimitedInt* a = new UnlimitedInt(i1->get_p_str());
    UnlimitedInt* b = new UnlimitedInt(i1->get_q_str());
    UnlimitedInt* c = new UnlimitedInt(i2->get_p_str());
    UnlimitedInt* d = new UnlimitedInt(i2->get_q_str());

    UnlimitedInt* p1p2 = UnlimitedInt::mul(a,c);
    UnlimitedInt* q1q2 = UnlimitedInt::mul(b,d);
    UnlimitedRational* res1 = new UnlimitedRational(p1p2,q1q2);

    delete p1p2;
    delete q1q2;
    delete a;
    delete b;
    delete c;
    delete d;
    delete res;

    return res1;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    
    UnlimitedInt* x = new UnlimitedInt("0");
    UnlimitedInt* y = new UnlimitedInt("0");
    UnlimitedRational* res = new UnlimitedRational(x,y);
    if(i1->get_frac_str() == "0/0" || i2->get_frac_str() == "0/0" || i2->get_p_str() == "0"){
        return res;
    }
    delete x;
    delete y;

    UnlimitedInt* a = new UnlimitedInt(i1->get_p_str());
    UnlimitedInt* b = new UnlimitedInt(i1->get_q_str());
    UnlimitedInt* c = new UnlimitedInt(i2->get_p_str());
    UnlimitedInt* d = new UnlimitedInt(i2->get_q_str());

    UnlimitedInt* p1q2 = UnlimitedInt::mul(a,d);
    UnlimitedInt* p2q1 = UnlimitedInt::mul(b,c);
    UnlimitedRational* res1 = new UnlimitedRational(p1q2,p2q1);

    delete p1q2;
    delete p2q1;
    delete a;
    delete b;
    delete c;
    delete d;
    delete res;

    return res1;
}
