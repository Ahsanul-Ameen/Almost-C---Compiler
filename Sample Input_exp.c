int main(){
    int a,b,c[3];
    a = 1*(2+3)%3;
    b = 1<5;
    c[0] = 2;
    c[1] = 2;
    if(a && b)
        c[1]++;
    else
        c[1] = c[0];
    println(a);
    println(b);
    int d;
    d = c[0];
    println(d);
    d = c[1];
    println(d);
}

