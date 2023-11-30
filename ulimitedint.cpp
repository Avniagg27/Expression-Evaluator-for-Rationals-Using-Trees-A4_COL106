/* Do NOT add/rove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
UnlimitedInt::UnlimitedInt(){
    size = 1;
    sign = 1;
    capacity =27;
    unlimited_int = new int[capacity]{};
}

UnlimitedInt::~UnlimitedInt(){
    delete[] unlimited_int;
}

UnlimitedInt::UnlimitedInt(string s){
    size = s.length();
    if(s[0]=='-'){
        sign = -1;
        s = s.substr(1);
        size--;
    }
    else if(size == 1 && s[0]=='0'){
        sign = 0;
    }
    else {
        sign = 1;
    }
    capacity = size;
    unlimited_int = new int[capacity]{};
    
        for(int i = 0; i < size; i++){
            unlimited_int[i]= s[size-i-1]-'0';
        }    
}

UnlimitedInt::UnlimitedInt(int i){
    size = 0;
    if(i<0){
        sign = -1;
    }
    else if(i==0){
        sign = 0;
    }
    else{
        sign = 1;
    }
    capacity = 27;
    unlimited_int = new int[capacity]{};
    if(i==0){
        size = 1;
    }
    else{
        i = abs(i);
        while(i>0){
            if(size== capacity){
                int* arr = new int[2*capacity]{};
                for(int j = 0; j<size; j++){
                    arr[j] = unlimited_int[j];
                }
                delete[] unlimited_int;
                unlimited_int = arr;
                capacity= capacity*2; 
            }
            unlimited_int[size++] = i % 10;
            i = i/10;
        }
    }
}

UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz) {
    capacity = cap;
    size = sz;
    sign = sgn;
    unlimited_int = new int[capacity];
    
    for (int i = 0; i < capacity; i++) {
        unlimited_int[i] = ulimited_int[i];
    }
    size = capacity;
}

int UnlimitedInt::get_size(){
    return size;
}

int* UnlimitedInt::get_array(){
    return unlimited_int;
}

int UnlimitedInt::get_sign(){
    return sign;
}

int UnlimitedInt::get_capacity(){
    return capacity;
}

string UnlimitedInt::to_string(){
    if(sign ==0){
        return "0";
    }
    string s1 = "";
    if(sign == -1){
        s1 = '-' + s1;
    }
    for(int i= 0; i<size; i++){
        s1 = s1 + std::to_string(unlimited_int[size-i-1]);
    }
    if(s1=="-0"){
        s1 = "0";
        sign = 0;
    }
    return s1;
}

int comp_abs(UnlimitedInt* i1,UnlimitedInt* i2) {
    
    if (i1->get_size() > i2->get_size()) {
        return 1;
    } else if (i1->get_size() < i2->get_size()) {
        return -1;
    }
    int* a = i1->get_array();
    int* b = i2->get_array();
    for (int i = i1->get_size()-1; i >0; i--) {
        if (a[i] > b[i]) {
            return 1;
        } else if (a[i] < b[i]) {
            return -1;
        }
    }
    if(a[0]>b[0]){
        return 1;
    }
    else if(a[0]<b[0]){
        return -1;
    }
    return 0;
}

UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2) {
    if (i1->sign == 0) {
        return new UnlimitedInt(i2->to_string());
    }
    if (i2->sign == 0) {
        return new UnlimitedInt(i1->to_string());
    }

    UnlimitedInt* greater = (i1->size >= i2->size) ? i1 : i2;
  
    int fin_size = greater->size + 1;

    int fin_sign;
    int* fin_arr = new int[fin_size]{};
    
    if (i1->sign*i2->sign == 1) {
        if(i1->sign == -1 && i2->sign == -1){
            fin_sign = -1;
        }
        else{
            fin_sign = 1;
        }

        int carry = 0; 
        int idx1 = 0;
        int idx2 = 0;
        int res1 = 0;

        while (res1 < fin_size) {
            int sum = carry;
            if (idx1 <i1->size) {
                sum += (i1->unlimited_int[idx1] * i1->sign); 
                idx1++;
            }
            if (idx2 <i2->size) {
                sum += (i2->unlimited_int[idx2] * i2->sign);
                idx2++;
            }
            carry = sum / 10; 
            fin_arr[res1] = abs(sum) % 10; 
            res1++;
        }

        if (carry > 0) {
            fin_arr[res1] = carry;
        }

    }
    else {
        if(i1->sign == 1 && i2->sign == -1){
            if(comp_abs(i1,i2)>=0){
                fin_sign = 1;
            }
            else{
                fin_sign = -1;
            }
        }
        else{
            if(comp_abs(i1,i2)>=0){
                fin_sign = -1;
            }
            else{
                fin_sign = 1;
            }
        }
        if(comp_abs(i1,i2)>=0){
            int bor = 0;
            int idx1 = 0;
            int idx2 = 0;
            int residx = 0;

            while(residx<fin_size-1){
                int diff = bor;
                if(idx1<i1->size){
                    diff += i1->unlimited_int[idx1];
                    idx1++;
                }
                if(idx2<i2->size){
                    diff -= i2->unlimited_int[idx2];
                    idx2++;
                }
                if(diff<0){
                    bor = -1;
                    diff += 10;
                }else{
                    bor =0;
                }
                fin_arr[residx] = diff;
                residx++;
            }
        }
        else{
            int bor = 0;
            int idx1 = 0;
            int idx2 = 0;
            int residx = 0;

            while(residx<fin_size-1){
                int diff = bor;
                if(idx1<i1->size){
                    diff -= i1->unlimited_int[idx1];
                    idx1++;
                }
                if(idx2<i2->size){
                    diff += i2->unlimited_int[idx2];
                    idx2++;
                }
                if(diff<0){
                    bor = -1;
                    diff += 10;
                }else{
                    bor = 0;
                }
                fin_arr[residx] = diff;
                residx++;
            }
        }
    }

    while (fin_size > 1 && fin_arr[fin_size - 1] == 0) {
        fin_size--;
    }
    
    return new UnlimitedInt(fin_arr, fin_size, fin_sign, fin_size);
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2) {
    if(i1->sign==0 && i2->sign == 0){
        return new UnlimitedInt("0");
    }
    if (i2->sign == 0) {
        return new UnlimitedInt(i1->to_string());
    }
    if (i1->sign == 0) {
        UnlimitedInt* i3 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), -i2->sign, i2->get_size());
        return new UnlimitedInt(i3->to_string());
    }
    UnlimitedInt* greater = (i1->size >= i2->size) ? i1 : i2;
  
    int fin_size = greater->size + 1;

    int fin_sign;
    int* fin_arr = new int[fin_size]{};
    
    if (i1->sign*i2->sign == -1) {
        if(i1->sign == -1 && i2->sign == -1){
            fin_sign = -1;
        }
        else{
            fin_sign = 1;
        }

        int carry = 0; 
        int idx1 = 0;
        int idx2 = 0;
        int res1 = 0;

        while (res1 < fin_size) {
            int sum = carry;
            if (idx1 <i1->size) {
                sum += (i1->unlimited_int[idx1] * i1->sign); 
                idx1++;
            }
            if (idx2 <i2->size) {
                sum += (i2->unlimited_int[idx2] * i2->sign);
                idx2++;
            }
            carry = sum / 10; 
            fin_arr[res1] = abs(sum) % 10; 
            res1++;
        }

        if (carry > 0) {
            fin_arr[res1] = carry;
        }

    }
    else {
        if(i1->sign == 1 && i2->sign == 1){
            if(comp_abs(i1,i2)>=0){
                fin_sign = 1;
            }
            else{
                fin_sign = -1;
            }
        }
        else{
            if(comp_abs(i1,i2)>=0){
                fin_sign = -1;
            }
            else{
                fin_sign = 1;
            }
        }
        if(comp_abs(i1,i2)>=0){
            int bor = 0;
            int idx1 = 0;
            int idx2 = 0;
            int residx = 0;

            while(residx<fin_size-1){
                int diff = bor;
                if(idx1<i1->size){
                    diff += i1->unlimited_int[idx1];
                    idx1++;
                }
                if(idx2<i2->size){
                    diff -= i2->unlimited_int[idx2];
                    idx2++;
                }
                if(diff<0){
                    bor = -1;
                    diff += 10;
                }else{
                    bor =0;
                }
                fin_arr[residx] = diff;
                residx++;
            }
        }
        else{
            int bor = 0;
            int idx1 = 0;
            int idx2 = 0;
            int residx = 0;

            while(residx<fin_size-1){
                int diff = bor;
                if(idx1<i1->size){
                    diff -= i1->unlimited_int[idx1];
                    idx1++;
                }
                if(idx2<i2->size){
                    diff += i2->unlimited_int[idx2];
                    idx2++;
                }
                if(diff<0){
                    bor = -1;
                    diff += 10;
                }else{
                    bor = 0;
                }
                fin_arr[residx] = diff;
                residx++;
            }
        }
    }

    while (fin_size > 1 && fin_arr[fin_size - 1] == 0) {
        fin_size--;
    }
    
    return new UnlimitedInt(fin_arr, fin_size, fin_sign, fin_size);
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2) {
    if(i1->sign==0 || i2->sign==0){
        return new UnlimitedInt("0");
    }
    int fin_sign;
    if(i1->get_sign() == i2->get_sign()){
        fin_sign = 1;
    }
    else{
        fin_sign = -1;
    }
    int siz1 = i1->get_size();
    int siz2 = i2->get_size();
    int fin_siz = siz1 + siz2;
    int* fin_arr = new int[fin_siz]{};
    for (int i = 0; i < fin_siz; i++) {
        fin_arr[i] = 0;
    }

    for (int i = 0; i < siz1; i++) {
        for (int j = 0; j < siz2; j++) {
            fin_arr[i + j] += i1->get_array()[i] * i2->get_array()[j];
        }
    }

    int carry = 0;
    for (int i = 0; i < fin_siz; i++) {
        fin_arr[i] += carry;
        carry = fin_arr[i] / 10;
        fin_arr[i] %= 10;
    }
    while (fin_siz > 1 && fin_arr[fin_siz - 1] == 0) {
       fin_siz--;
   }
    UnlimitedInt* final = new UnlimitedInt(fin_arr, fin_siz, fin_sign, fin_siz);

    delete[] fin_arr;

    return final;   
}

UnlimitedInt* half(UnlimitedInt* x) {
    int n = x->get_size();
    int* arr = new int[n];

    int* d = x->get_array();
    int c = 0;

    for(int i = 0; i < n; i++) {
        int sum = c*10 + d[n-1-i];
        arr[n-1-i] = sum / 2;
        c = sum % 2;
    }

    if(arr[n-1] == 0) {
        n--;
    }

    int* fin_arr = new int[n];
    for(int j = 0; j < n; j++) {
        fin_arr[j] = arr[j];
    }

    delete[] arr;
    UnlimitedInt* res = new UnlimitedInt(fin_arr, n, x->get_sign(), n);
    return res;
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2){
    if(i1->sign == 0){
        return new UnlimitedInt("0");
    }
    if(comp_abs(i1, i2) == -1 && i1->get_sign() == i2->get_sign()){
        return new UnlimitedInt("0");
    }
    if(comp_abs(i1,i2)== -1 && i1->get_sign()!=i2->get_sign()){
        return new UnlimitedInt("-1");
    }
    else{
        int diff = i1->size - i2->size;
        int diff2 = diff + 2;
        if(diff == 0){
            diff++;
        }
        bool check_sign = 0;
        if(i1->get_sign() == -1 && i2->get_sign()==-1){
            i1->sign = i2->sign = 1;
            check_sign = 1;
        }
        
        int* arr1 = new int[diff];
        for(int i = 0; i < diff-1; i++){
            arr1[i] = 0;
        }
        int* arr2 = new int[diff2];
        for(int j = 0; j < diff2-1; j++){
            arr2[j] = 0;
        }

        arr1[diff-1] = 1;
        arr2[diff2-1] = 1;

        UnlimitedInt* a = new UnlimitedInt(arr1, diff, 1, diff);
        UnlimitedInt* b = new UnlimitedInt(arr2, diff2, 1, diff2);
        delete[] arr1;
        delete[] arr2;

        UnlimitedInt* temp = UnlimitedInt::add(b, a);
        UnlimitedInt* c = half(temp);
        UnlimitedInt* mult = UnlimitedInt::mul(i2, c);
        UnlimitedInt* subt = UnlimitedInt::sub(i1, mult); 
        delete temp;


        while(comp_abs(subt, i2) >= 0 || subt->sign < 0) {
            if(subt->sign < 0){
                delete b;
                b = new UnlimitedInt(c->unlimited_int, c->capacity, c->sign, c->size);
            }
            else{
                delete a;
                a = new UnlimitedInt(c->unlimited_int, c->capacity, c->sign, c->size);
            }
            delete c;
            delete mult;
            delete subt;
            
            temp = UnlimitedInt::add(b, a);
            c = half(temp);
            mult = UnlimitedInt::mul(i2, c);
            subt = UnlimitedInt::sub(i1, mult);
            delete temp;

        }

        delete mult;
        delete subt;
        if(check_sign == 1){
            i1->sign = i2->sign = -1;
        }
        return c;
    }
    
    if(i1->sign*i2->sign == -1) {
            UnlimitedInt* x = new UnlimitedInt(i1->unlimited_int, i1->capacity, 1, i1->size); 
            UnlimitedInt* y = new UnlimitedInt(i2->unlimited_int, i2->capacity, 1, i2->size);
            UnlimitedInt* z;
            UnlimitedInt* w;
            UnlimitedInt* mult;
            UnlimitedInt* t = new UnlimitedInt("1");

            z = UnlimitedInt::div(x, y);
            mult = UnlimitedInt::mul(z, y);

            if(comp_abs(x, mult) != 0){
                w = UnlimitedInt::add(z, t);
                w->sign = -1;
            }
            else{
                w = new UnlimitedInt(z->unlimited_int, z->capacity, -1, z->size);
            } 
            delete mult;
            delete z;
            delete t;
            delete x;
            delete y;

            return w;
    }
    return nullptr;
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2){
    UnlimitedInt* a = new UnlimitedInt(i1->to_string());
    UnlimitedInt* b = new UnlimitedInt(i2->to_string());
    UnlimitedInt* p = UnlimitedInt::div(a,b);
    UnlimitedInt* q = UnlimitedInt::mul(b,p);
    UnlimitedInt* r = UnlimitedInt::sub(a,q);
    delete a;
    delete b;
    return new UnlimitedInt(r->to_string());
}
