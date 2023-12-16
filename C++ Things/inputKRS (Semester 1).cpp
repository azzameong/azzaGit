#include <iostream>
using namespace std;

int main() {

int pilihMenu, pilihKRS, ipk, brpMatkul, sc, sks, nomMatkul, x=0, print[x], i=0;
int bi=0, bing=0, rel=0, sisdig=0, sismik=0, pemdas=0, pemlan=0, komdat=0;
double ipk;
string username, password;
string uname[5], pw[5];
string mataKul[8]={"Bahasa Indonesia \t \t \t ( 2 sks )","Bahasa Inggris \t \t \t ( 2 sks )",
"Rangkaian elektronika lanjut \t ( 4 sks )", "Sistem Digital \t \t \t ( 3 sks )",
"Sistem Mikrokontroler \t \t ( 4 sks )","Pemrogaman Dasar \t \t \t ( 3 sks )",
"Pemrogaman Lanjut \t \t \t ( 4 sks )", "Komunikasi Data \t \t \t ( 2 sks )"};

menu :
cout << "1. Registrasi" << endl;
cout << "2. Login" << endl;
cout << "Masukkan pilihan anda : ";
cin >> pilihMenu;
switch(pilihMenu){
  case 1 :
  //Registrasi :
  if (i<5){
    cout << "Masukkan username : ";
    cin.ignore();
    getline(cin, uname[i]);
    cout << "Masukkan password : ";
    cin >> pw[i];
    i++;
    }
    //system("cls");
    goto menu;
    break;

  case 2 :
  //login :
  cout << "Masukkan username : ";
  cin.ignore();
  getline(cin, username);
  cout << "Masukkan password : ";
  cin >> password;
  for (i=0; i<5; i++){
  if (username == uname[i] && password == pw[i]){
  sc=1;}
    if (sc==1){
    cout << endl;
    goto pilihKRS;}
    else {
    cout << "Username dan password salah" << endl;
    goto menu;}
    }\

  default :
  system ("cls");
  goto menu;
  }

pilihKRS :
cout << "Hai! Selamat datang di SIAM UB" << endl;
cout << "Silahkan pilih : "<< endl;
cout << "1. Pilih KRS " << endl;
cout << "2. Cetak KRS" << endl;
cout << "3. Logout " << endl;
cout << "Pilihan anda : " << endl;
cin >> pilihKRS;
switch (pilihKRS){
  case 1 :
  cout << "Masukkan IPK anda : ";
  cin >> ipk;
  if (ipk < 3.00){
    sks = 24;
    goto menuKRS;}
  else if (ipk >= 3.00 && ipk <=4.00){
    sks = 20;
    goto menuKRS;}
  else {
    cout << "Mohon maaf IPK yang anda inputkan tidak sesuai";
    goto pilihKRS;}

menuKRS :
  cout << "SKS kamu semester ini maksimal : "<< sks << "sks" << endl;
  cout << "Mata kuliah yang tersedia : " << endl;
  for (int x = 0; x < 8; x++){
  cout << x+1 << ". " << mataKul[x] << endl;}
  cout << "Ingin mengambil berapa mata kuliah ? \n";
  cout << "Jawab : ";
  cin >> brpMatkul;
  cout << endl;
  if (brpMatkul<=8){
    for (x=0; x<brpMatkul; x++){
    nomorMatkul:
    cout << "Masukkan nomor mata kuliah : ";
    cin >> nomMatkul;
    if(sks != 0){
    if (nomMatkul ==1 && bi==0 ){
    cout << mataKul[0] << endl;
    sks -= 2;
    bi++;
    print[x]=nomMatkul-1;}
    else if (nomMatkul ==2 && bing==0){
    cout << mataKul[1] << endl;
    sks -= 2;
    bing++;
    print[x]=nomMatkul-1;}
    else if (nomMatkul ==3 && rel==0){
    cout << mataKul[2] << endl;
    sks -= 4;
    rel++;
    print[x]=nomMatkul-1;}
    else if (nomMatkul ==4 && sisdig==0){
    cout << mataKul[3] << endl;
    sks -= 3;
    sisdig++;
    print[x]=nomMatkul-1;}
    else if (nomMatkul ==5 && sismik==0){
    cout << mataKul[4] << endl;
    sks -= 4;
    sismik++;
    print[x]=nomMatkul-1;}
    else if (nomMatkul ==6 && pemdas==0){
    cout << mataKul[5] << endl;
    sks -= 3;
    pemdas++;
    print[x]=nomMatkul-1;}
    else if (nomMatkul ==7 && pemlan==0){
    cout << mataKul[6] << endl;
    sks -= 4;
    pemlan++;
    print[x]=nomMatkul-1;}
    else if (nomMatkul ==8 && komdat==0){
    cout << mataKul[7] << endl;
    sks -= 2;
    komdat++;
    print[x]=nomMatkul-1;}
    else{
    cout << "SKS melebihi batas atau terdapat matakuliah yang sama" << endl;
    x--;
    goto nomorMatkul;}
    }
  }
  cout << endl;
  goto pilihKRS;
  }
  else{
  system ("cls");
  cout << "Mata kuliah maksimal 8" << endl;
  goto menuKRS;}
  break;
  
  //cetak KRS
  case 2 :
  cout << "KRS Akademik Universitas Brawijaya" << endl;
  cout << "Mata kuliah yang anda ambil disemester ini" << endl;
  for (x=0; x<brpMatkul; x++){
  cout << x+1 << ". " << mataKul[print[x]] <<
  endl;}
  goto pilihKRS;
  break;
  
  //logout
  case 3 :
  system ("cls");
  cout << "Terima kasih";
  break;
  
  //lainnya
  default :
  system ("cls");
  goto pilihKRS;
  }
return 0;
}
