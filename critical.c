int glb[100], aula;

void foo();
void foo(){
  println(aula);
}

void fooa(int xx, int yy) {

}

int fib(int n) {
  int ara[100];
  ara[0] = 0;
  ara[1] = 1;
  int i;
  for(i = 2; i <= n; i++) {
    ara[i] = ara[i-1] + ara[i-2];
  }
  return ara[n];
}

int fibRec(int n) {
  if(n<=1) return n;
  return fibRec(n-1) + fibRec(n-2);
}

int gcd(int x, int y) {
  if(y == 0)return x;
  else return gcd(y, x%y);
}

int main() {

  foo();
  fooa(44/4, 45/5);

  int var;
  int arr[20];
  arr[0] = 10;
  var = arr[0];
  println(var);//10
  arr[1] = arr[0];
  var = arr[1];
  println(var);//10
  var = 2;
  arr[var] = arr[var-1] + arr[var-2];//20
  var = arr[var];
  println(var);//20
  var = arr[2] + arr[1] + arr[0] + var;
  println(var);//60
  var = 5;
  var = fib(var);
  println(var);//5
  var = fib(6);
  println(var);//8

  var = 0;
  while(var < 10) {
    glb[var] = (var + var)/2;
    aula = glb[var]*glb[var];
    var++;
    println(aula);//0..1..4...9....
  }

  int i, j;
  var = 0;
  for(i = 0; i < 6; i++) {
    for(j = i+1; j < 6; j++) {
      int g;
      //g = gcd(i, j);
      var = var + gcd(i, j);
    }
  }
  println(var);//26

  return 0;
}

