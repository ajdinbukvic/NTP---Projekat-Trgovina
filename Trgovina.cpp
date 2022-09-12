/*----------------------------------------------------
Naziv projekta: Trgovina
Autor: Ajdin Bukvic
ajdin.bukvic.20@size.ba
Predmet: Napredne tehnike programiranja
PTF UNZE - 2020/2021
----------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <cstdlib>
using namespace std;
//----------------------------------------------------
struct korisnik{
	char ime[30];
	char prezime[30];
	char korisnicko_ime[30];
	char lozinka[30];
	float racun;
};
struct proizvod{
	int rb;
	char naziv[30];
	float cijena;
	bool popust;
	int kolicina;
};
struct narudzba{
	int sifra;
	korisnik kupac;
	proizvod kupljen;
	bool placeno;
};
//----------------------------------------------------
int menu();
bool provjera_k_ime(char[]);
void registracija();
bool provjera_lozinke(char[],char[]);
void prijava();
int glavni_menu();
void stanje_na_racunu(korisnik*);
int prebroj_korisnike();
void azuriraj_novac(korisnik*,int,int,float);
void dodaj_novac(korisnik*,int);
void lista_proizvoda();
int prebroj_proizvode();
void azuriraj_proizvode(proizvod*,int,int);
void naruci_proizvod(korisnik*,int);
void pregled_narudzbe(korisnik*);
int prebroj_narudzbe();
void azuriraj_narudzbe(narudzba*,int,int);
void azuriraj_narudzbe(korisnik*,int,int,float);
void plati_narudzbu(korisnik*,int,int);
//----------------------------------------------------
int main()
{
	int odabir; 
	while(odabir = menu()){ 
		switch(odabir){ 
			case 1:{
				system("cls");
				registracija();
				break;
			}
			case 2:{
				system("cls");
				prijava();
				break;
			}
			case 3:{
				exit(EXIT_FAILURE);
			}
		}
		cout<<"\nPritisnite bilo koju tipku za nastavak...";
		getch();
	}
	return 0;
}
//----------------------------------------------------
int menu(){
	system("cls");
	cout<<"\t\t\t\t---------------------------------------------------\n";
	cout<<"\t\t\t\t\tDOBRO DOSLI U SISTEM ONLINE TRGOVINE\n";
	cout<<"\t\t\t\t---------------------------------------------------\n";
	cout<<"\t\t\t\t\t1. Registracija\n";
	cout<<"\t\t\t\t\t2. Prijava\n";
	cout<<"\t\t\t\t\t3. Izlaz\n";
	cout<<"\t\t\t\t---------------------------------------------------\n";
	cout<<"\t\t\t\tODABIR: ";
	int n;
	cin>>n; 
	if(cin) return n; 
	else{
		cin.clear();
		cin.ignore(100, '\n');
		return 0;
	}
}
bool provjera_k_ime(char unos[30]){
	korisnik k;
	ifstream ulaz("korisnici.txt");
	if(ulaz.is_open()){
		while(ulaz >> k.ime >> k.prezime >> k.korisnicko_ime >> k.lozinka >> k.racun){
			if(strcmp(unos, k.korisnicko_ime) == 0) {
				return true;
			}
		}
		return false;
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke korisnici.txt nije uspjelo!"<<endl;
		return 0;
	}
	ulaz.close();
}
void registracija(){
	cin.ignore();
	korisnik k;
	ofstream izlaz("korisnici.txt", ios::app);
	if(izlaz.is_open()){
		cout<<"Unesite ime: ";
		cin.getline(k.ime, 30);
		cout<<"Unesite prezime: ";
		cin.getline(k.prezime, 30);
		do{
			cout<<"Unesite korisnicko ime: ";
			cin.getline(k.korisnicko_ime, 30);
			if(provjera_k_ime(k.korisnicko_ime)) cout<<"Unesite drugo korisnicko ime, jer to vec postoji!"<<endl;
		}
		while(provjera_k_ime(k.korisnicko_ime));
		cout<<"Unesite lozinku: ";
		cin.getline(k.lozinka, 30);
		k.racun = 2000;
		izlaz << k.ime << " " << k.prezime << " " << k.korisnicko_ime << " " << k.lozinka << " " << k.racun << endl;
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke korisnici.txt nije uspjelo!"<<endl;
		return;
	}
	izlaz.close();
	cout<<"\n\n\n\n";
	cout<<"Uspjesno ste se registrovali na nas sistem!"<<endl;
	cout<<"Sada se morate ponovo prijaviti u sistem..."<<endl;
	cout<<"Spremanje podataka..."<<endl;
	Sleep(2000);
	return;
}
bool provjera_lozinke(char unos_k_ime[30], char unos_lozinka[30]){
	korisnik k;
	ifstream ulaz("korisnici.txt");
	if(ulaz.is_open()){
		while(ulaz >> k.ime >> k.prezime >> k.korisnicko_ime >> k.lozinka >> k.racun){
			if(strcmp(unos_k_ime, k.korisnicko_ime) == 0 && strcmp(unos_lozinka, k.lozinka) == 0) {
				return true;
			}
		}
		return false;
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke korisnici.txt nije uspjelo!"<<endl;
		return 0;
	}
	ulaz.close();
}
int glavni_menu(){
	system("cls");
	cout<<"\t\t\t\t---------------------------------------------------\n";
	cout<<"\t\t\t\t\tDOBRO DOSLI U MENU ONLINE TRGOVINE\n";
	cout<<"\t\t\t\t---------------------------------------------------\n";
	cout<<"\t\t\t\t\t1. Stanje na racunu\n";
	cout<<"\t\t\t\t\t2. Dodaj novac\n";
	cout<<"\t\t\t\t\t3. Lista proizvoda\n";
	cout<<"\t\t\t\t\t4. Naruci proizvod\n";
	cout<<"\t\t\t\t\t5. Pregled narudzbi\n";
	cout<<"\t\t\t\t\t6. Plati narudzbu\n";
	cout<<"\t\t\t\t\t7. Izlaz\n";
	cout<<"\t\t\t\t---------------------------------------------------\n";
	cout<<"\t\t\t\tODABIR: ";
	int n;
	cin>>n; 
	if(cin) return n; 
	else{
		cin.clear();
		cin.ignore(100, '\n');
		return 0;
	}
}
void prijava(){
	cin.ignore();
	korisnik k;
	int pokusaji_i = 3;
	int pokusaji_l = 3;
	do{
		cout<<"Unesite korisnicko ime: ";
		cin.getline(k.korisnicko_ime, 30);
		if(!provjera_k_ime(k.korisnicko_ime)){
			cout<<"Uneseno korisnicko ime ne postoji!"<<endl;
			pokusaji_i--;
		}
		if(pokusaji_i == 0){
			cout<<"\nPogrijesili ste previse puta sa unosom..."<<endl;
			Sleep(2000);
			return;
		}
	}
	while(!provjera_k_ime(k.korisnicko_ime));
	do{
		cout<<"Unesite lozinku: ";
		cin.getline(k.lozinka, 30);
		if(!provjera_lozinke(k.korisnicko_ime, k.lozinka)){
			cout<<"Unesena lozinka se ne podudara sa korisnickim imenom!"<<endl;
			pokusaji_l--;
		}
		if(pokusaji_l == 0){
			cout<<"\nPogrijesili ste previse puta sa unosom..."<<endl;
			Sleep(2000);
			return;
		}
	}
	while(!provjera_lozinke(k.korisnicko_ime, k.lozinka));
	cout<<"\n\n\n\n";
	cout<<"Uspjesno ste se prijavili na nas sistem!"<<endl;
	cout<<"Sada imate pristup glavnom meniju naseg sistema..."<<endl;
	cout<<"Ucitavanje..."<<endl;
	Sleep(2000);
	int odabir;
	while(odabir = glavni_menu()){ 
		switch(odabir){ 
			case 1:{
				system("cls");
				stanje_na_racunu(&k);
				break;
			}
			case 2:{
				system("cls");
				int br = prebroj_korisnike();
				dodaj_novac(&k,br);
				break;
			}
			case 3:{
				system("cls");
				lista_proizvoda();
				break;
			}
			case 4:{
				system("cls");
				int br = prebroj_proizvode();
				naruci_proizvod(&k,br);
				break;
			}
			case 5:{
				system("cls");
				pregled_narudzbe(&k);
				break;
			}
			case 6:{
				system("cls");
				int br = prebroj_narudzbe();
				int br_k = prebroj_korisnike();
				plati_narudzbu(&k,br,br_k);
				break;
			}
			case 7:{
				exit(EXIT_FAILURE);
			}
		}
		cout<<"\nPritisnite bilo koju tipku za nastavak...";
		getch();
	}
}
void stanje_na_racunu(korisnik *k){
	korisnik temp;
	ifstream ulaz("korisnici.txt");
	if(ulaz.is_open()){
		while(ulaz >> temp.ime >> temp.prezime >> temp.korisnicko_ime >> temp.lozinka >> temp.racun){
			if(strcmp(k->korisnicko_ime, temp.korisnicko_ime) == 0) {
				cout<<"Stanje na vasem racunu iznosi: "<<temp.racun<<" KM."<<endl;
			}
		}
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke korisnici.txt nije uspjelo!"<<endl;
		return;
	}
	ulaz.close();
}
int prebroj_korisnike(){
	int br_korisnika = 0;
	korisnik temp;
	ifstream ulaz("korisnici.txt");
	if(ulaz.is_open()){
		while(ulaz >> temp.ime >> temp.prezime >> temp.korisnicko_ime >> temp.lozinka >> temp.racun){
			br_korisnika++;
		}
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke korisnici.txt nije uspjelo!"<<endl;
		return 0;
	}
	ulaz.close();
	return br_korisnika;
}
void azuriraj_novac(korisnik *niz, int br_korisnika, int pozicija, float novac){
	ofstream izlaz("korisnici.txt");
	if(izlaz.is_open()){
		for(int i = 0; i<br_korisnika; i++){
			if(i == pozicija){
				izlaz << niz[i].ime << " " << niz[i].prezime << " " << niz[i].korisnicko_ime << " " << niz[i].lozinka << " " << niz[i].racun+novac << endl;
			}
			else{
				izlaz << niz[i].ime << " " << niz[i].prezime << " " << niz[i].korisnicko_ime << " " << niz[i].lozinka << " " << niz[i].racun << endl;
			}
		}
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke korisnici.txt nije uspjelo!"<<endl;
		return;
	}
	izlaz.close();
}
void dodaj_novac(korisnik *k, int br_korisnika){
	korisnik *niz = new korisnik[br_korisnika];
	korisnik temp;
	int br = 0;
	int pozicija;
	float novac;
	do{
		cout<<"Unesite koliko zelite dodati novca (100 - 1000): ";
		cin>>novac;
		if(novac < 100 || novac > 1000) cout<<"Mozete dodati novac samo u intervalu 100 - 1000!"<<endl;
	}
	while(novac < 100 || novac > 1000);
	ifstream ulaz("korisnici.txt");
	if(ulaz.is_open()){
		while(ulaz >> temp.ime >> temp.prezime >> temp.korisnicko_ime >> temp.lozinka >> temp.racun){
			niz[br] = temp;
			br++;
			if(strcmp(k->korisnicko_ime,temp.korisnicko_ime) == 0){
				pozicija = br-1;
				cout<<"Uspjesno ste dodali novac na vas racun!"<<endl;
				cout<<"Staro stanje: "<<temp.racun<<" KM"<<endl;
				cout<<"Novo stanje: "<<temp.racun+novac<<" KM"<<endl;
			}
		}
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke korisnici.txt nije uspjelo!"<<endl;
		return;
	}
	ulaz.close();
	azuriraj_novac(niz, br_korisnika, pozicija, novac);
	delete[] niz;
}
void lista_proizvoda(){
	proizvod temp;
	ifstream ulaz("proizvodi.txt");
	if(ulaz.is_open()){
		cout<<"\t\t\t\t---------------------------------------------------\n";
		cout<<"\t\t\t\t\t\tDostupni proizvodi"<<endl;
		cout<<"\t\t\t\t---------------------------------------------------\n";
		cout<<"\t\t\t\t"<<left<<setw(5)<<"RB"<<setw(12)<<"Naziv"<<setw(14)<<"Cijena"<<setw(10)<<"Popust"<<setw(10)<<"Kolicina"<<endl;
		cout<<"\t\t\t\t---------------------------------------------------\n";
		while(ulaz >> temp.rb >> temp.naziv >> temp.cijena >> temp.popust >> temp.kolicina){
			if(temp.popust == 0){
				cout<<"\t\t\t\t"<<left<<setw(5)<<temp.rb<<left<<setw(15)<<temp.naziv<<setw(12)<<temp.cijena<<setw(10)<<"NE"<<setw(10)<<temp.kolicina<<endl;
			} 
			else{
				cout<<"\t\t\t\t"<<left<<setw(5)<<temp.rb<<left<<setw(15)<<temp.naziv<<setw(12)<<temp.cijena<<setw(10)<<"DA"<<setw(10)<<temp.kolicina<<endl;
			}
		}
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke proizvodi.txt nije uspjelo!"<<endl;
		return;
	}
	ulaz.close();
}
int prebroj_proizvode(){
	int br_proizvoda = 0;
	proizvod temp;
	ifstream ulaz("proizvodi.txt");
	if(ulaz.is_open()){
		while(ulaz >> temp.rb >> temp.naziv >> temp.cijena >> temp.popust >> temp.kolicina){
			br_proizvoda++;
		}
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke proizvodi.txt nije uspjelo!"<<endl;
		return 0;
	}
	ulaz.close();
	return br_proizvoda;
}
void azuriraj_proizvode(proizvod *niz, int br_proizvoda, int pozicija){
	ofstream izlaz("proizvodi.txt");
	if(izlaz.is_open()){
		for(int i = 0; i<br_proizvoda; i++){
			if(i == pozicija){
				izlaz << niz[i].rb << " " << niz[i].naziv << " " << niz[i].cijena << " " << niz[i].popust << " " << niz[i].kolicina-1 << endl;
			}
			else{
				izlaz << niz[i].rb << " " << niz[i].naziv << " " << niz[i].cijena << " " << niz[i].popust << " " << niz[i].kolicina << endl;
			}
		}
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke proizvodi.txt nije uspjelo!"<<endl;
		return;
	}
	izlaz.close();
}
void naruci_proizvod(korisnik *k, int br_proizvoda){
	proizvod *niz = new proizvod[br_proizvoda];
	int br = 0;
	proizvod temp;
	int unos;
	int pozicija;
	korisnik pom;
	float racun_kupca;
	ifstream ulaz_k("korisnici.txt");
	if(ulaz_k.is_open()){
		while(ulaz_k >> pom.ime >> pom.prezime >> pom.korisnicko_ime >> pom.lozinka >> pom.racun){
			if(strcmp(k->korisnicko_ime, pom.korisnicko_ime) == 0) {
				racun_kupca = pom.racun;
			}
		}
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke korisnici.txt nije uspjelo!"<<endl;
		return;
	}
	ulaz_k.close();
	ifstream ulaz_p("proizvodi.txt");
	if(ulaz_p.is_open()){
		do{
			cout<<"Unesite redni broj proizvoda: ";
			cin>>unos;
			if(unos < 0 || unos > br_proizvoda) cout<<"Unijeli ste nepostojeci broj proizvoda! [Interval 1 - "<<br_proizvoda<<"]"<<endl;
		}
		while(unos < 0 || unos > br_proizvoda);
		while(ulaz_p >> temp.rb >> temp.naziv >> temp.cijena >> temp.popust >> temp.kolicina){
			niz[br] = temp;
			br++;
			if(unos == temp.rb && temp.kolicina > 0 && racun_kupca >= temp.cijena){
				srand(time(NULL));
				rand();
				int sifra = rand()%900+100;
				narudzba n;
				n.placeno = false;
				ofstream izlaz("narudzbe.txt", ios::app);
				if(izlaz.is_open()){
					izlaz << sifra << " " << k->korisnicko_ime<< " " << temp.naziv << " " << temp.cijena << " " << n.placeno << endl;
				}
				else{
					cout<<"[GRESKA]: Otvaranje datoteke narudzbe.txt nije uspjelo!"<<endl;
					return;
				}
				izlaz.close();
				cout<<"Uspjesno ste narucili proizvod..."<<endl;
				cout<<"Naziv: "<<temp.naziv<<endl;
				cout<<"Cijena: "<<temp.cijena<<" KM"<<endl;
				pozicija = temp.rb-1;
			}
			else if(unos == temp.rb && temp.kolicina < 1) cout<<"Taj proizvod vise nije dostupan za prodaju!"<<endl;
			else if(unos == temp.rb && racun_kupca < temp.cijena) cout<<"Nemate dovoljno novca na racunu za taj proizvod!"<<endl;
		}
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke proizvodi.txt nije uspjelo!"<<endl;
		return;
	}
	ulaz_p.close();
	azuriraj_proizvode(niz, br_proizvoda, pozicija);
	delete[] niz;
}
void pregled_narudzbe(korisnik *k){
	narudzba temp;
	int br_narudzbi = 0;
	ifstream ulaz("narudzbe.txt");
	if(ulaz.is_open()){
		cout<<"\t\t\t\t-----------------------------------------------\n";
		cout<<"\t\t\t\t\t\tVase narudzbe"<<endl;
		cout<<"\t\t\t\t-----------------------------------------------\n";
		cout<<"\t\t\t\t"<<left<<setw(10)<<"Sifra"<<setw(15)<<"Naziv"<<setw(15)<<"Cijena"<<setw(10)<<"Placeno"<<endl;
		cout<<"\t\t\t\t-----------------------------------------------\n";
		while(ulaz >> temp.sifra >> temp.kupac.korisnicko_ime >> temp.kupljen.naziv >> temp.kupljen.cijena >> temp.placeno){
			if(strcmp(k->korisnicko_ime, temp.kupac.korisnicko_ime) == 0){
				if(temp.placeno){
					cout<<"\t\t\t\t"<<left<<setw(10)<<temp.sifra<<setw(15)<<temp.kupljen.naziv<<setw(15)<<temp.kupljen.cijena<<setw(10)<<"DA"<<endl;
				}
				else{
					cout<<"\t\t\t\t"<<left<<setw(10)<<temp.sifra<<setw(15)<<temp.kupljen.naziv<<setw(15)<<temp.kupljen.cijena<<setw(10)<<"NE"<<endl;	
				}
				br_narudzbi++;
			}
		}
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke narudzbe.txt nije uspjelo!"<<endl;
		return;
	}
	ulaz.close();
	if(br_narudzbi == 0) cout<<"\t\t\t\tTrenutno nemate nijednu aktivnu narudzbu!"<<endl;
}
int prebroj_narudzbe(){
	int br_narudzbi = 0;
	narudzba temp;
	ifstream ulaz("narudzbe.txt");
	if(ulaz.is_open()){
		while(ulaz >> temp.sifra >> temp.kupac.korisnicko_ime >> temp.kupljen.naziv >> temp.kupljen.cijena >> temp.placeno){
			br_narudzbi++;
		}
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke narudzbe.txt nije uspjelo!"<<endl;
		return 0;
	}
	ulaz.close();
	return br_narudzbi;
}
void azuriraj_narudzbe(narudzba *niz, int br_narudzbi, int pozicija){
	ofstream izlaz("narudzbe.txt");
	if(izlaz.is_open()){
		for(int i = 0; i<br_narudzbi; i++){
			if(i == pozicija){
				niz[i].placeno = true;
				izlaz << niz[i].sifra << " " << niz[i].kupac.korisnicko_ime << " " << niz[i].kupljen.naziv << " " << niz[i].kupljen.cijena << " " << niz[i].placeno << endl;
			}
			else{
				izlaz << niz[i].sifra << " " << niz[i].kupac.korisnicko_ime << " " << niz[i].kupljen.naziv << " " << niz[i].kupljen.cijena << " " << niz[i].placeno << endl;
			}
		}
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke narudzbe.txt nije uspjelo!"<<endl;
		return;
	}
	izlaz.close();
}
void azuriraj_korisnike(korisnik *korisnici, int br_korisnika, int broj, float placeno){
	ofstream izlaz("korisnici.txt");
	if(izlaz.is_open()){
		for(int i = 0; i<br_korisnika; i++){
			if(i == broj){
				izlaz << korisnici[i].ime << " " << korisnici[i].prezime << " " << korisnici[i].korisnicko_ime << " " << korisnici[i].lozinka << " " << korisnici[i].racun-placeno << endl;
			}
			else{
				izlaz << korisnici[i].ime << " " << korisnici[i].prezime << " " << korisnici[i].korisnicko_ime << " " << korisnici[i].lozinka << " " << korisnici[i].racun << endl;
			}
		}
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke korisnici.txt nije uspjelo!"<<endl;
		return;
	}
	izlaz.close();
}
void plati_narudzbu(korisnik *k, int br_narudzbi, int br_korisnika){
	narudzba *niz = new narudzba[br_narudzbi];
	narudzba temp;
	int unos;
	int br = 0;
	int pozicija;
	bool postoji = false;
	float placeno;
	ifstream ulaz("narudzbe.txt");
	if(ulaz.is_open()){
		cout<<"Unesite sifru vase narudzbe: ";
		cin>>unos;
		while(ulaz >> temp.sifra >> temp.kupac.korisnicko_ime >> temp.kupljen.naziv >> temp.kupljen.cijena >> temp.placeno){
			niz[br] = temp;
			br++;
			if(unos == temp.sifra){
				if(temp.placeno){
					cout<<"Ova narudzba je vec placena!"<<endl;
					return;
				}
				else{
					cout<<"Uspjesno ste platili vasu narudzbu!"<<endl;
					cout<<"Sifra: "<<temp.sifra<<endl;
					cout<<"Cijena: "<<temp.kupljen.cijena<<" KM"<<endl;
					pozicija = br-1;
					placeno = temp.kupljen.cijena;	
				}
				postoji = true;
			}
		}
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke narudzbe.txt nije uspjelo!"<<endl;
		return;
	}
	ulaz.close();
	if(!postoji){
		cout<<"Unesena sifra ne odgovara nijednoj aktivnoj narudzbi!"<<endl;
		return;
	}
	azuriraj_narudzbe(niz, br_narudzbi, pozicija);
	korisnik *korisnici = new korisnik[br_korisnika];
	korisnik pom;
	int brojac = 0;
	int broj;
	ifstream ulaz_k("korisnici.txt");
	if(ulaz_k.is_open()){
		while(ulaz_k >> pom.ime >> pom.prezime >> pom.korisnicko_ime >> pom.lozinka >> pom.racun){
			korisnici[brojac] = pom;
			brojac++;
			if(strcmp(k->korisnicko_ime,pom.korisnicko_ime) == 0){
				broj = brojac-1;
				cout<<"Staro stanje: "<<pom.racun<<" KM"<<endl;
				cout<<"Novo stanje: "<<pom.racun-placeno<<" KM"<<endl;
			}
		}
	}
	else{
		cout<<"[GRESKA]: Otvaranje datoteke korisnici.txt nije uspjelo!"<<endl;
		return;
	}
	ulaz_k.close();
	azuriraj_korisnike(korisnici, br_korisnika, broj, placeno);
	delete[] niz;
	delete[] korisnici;
}
