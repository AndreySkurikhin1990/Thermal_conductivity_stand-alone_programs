#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>
#include <dos.h>
#include <iostream> 
#include <time.h>
using namespace std;
const int ceektp = 4, ds = 50, N = 13, ks = 10, dmkv = 28, cem = 11, dmkooscs = 14, nxts=65;
const int nnxts=0, vtn=0, vrsh=3;
const double tnoscs = 3e2, detes = 1e2, nnxtfs = 0.0, nxtfs = 65e0, y0sha = nxtfs*1e-3;
const double dtoscs = 1e2, pksvs = 0.0, tocrassha = 1e-6;
const double te0 = 273.15, dkoals = 0.647528, epsi = 1e-15; //dkoals - ïîëó÷åíèå ÊÏ èç ÊÎ
const char nf = 'F';
struct derevo {
	int otre; //1 - îòðàæåíèå èëè 0 - ïðîïóñêàíèå
	int ste; //íîìåð ñòåíêè
	int vis; //âèäèìîñòü: 1 - âèäåí, 0 - íåò
	int lev; //íîìåð óðîâíÿ
	struct derevo *back; //óêàçàòåëü íàçàä
	struct derevo *next; //óêàçàòåëü âïåðåä
};
class KoePog { public: double alp, tem; KoePog *nex; };
double *Tsh = NULL, *Ash = NULL, *Rsh = NULL, *Tash = NULL, *Aash = NULL, *Rash = NULL, *Ttsh = NULL, *Atsh = NULL, *Rtsh = NULL;
double *lxsha = NULL, *qxsha = NULL, *tkuscs = NULL, *kuscs = NULL, *qob = NULL, *tems = NULL, *etesha = NULL, *dtxsha = NULL;
double *dkosct = NULL, *kttk = NULL, *stchsrsha = NULL, *ktr = NULL, *ecktpsha = NULL, *Tpct = NULL, *dkoscm = NULL; //dkoscm - îòêëîíåíèå Ñ× (èëè ÏÑ) îò ëèòåðàòóðíûõ äàííûõ
double hsha, hvsha, hksha = 0.0, qobsha = 0.0, porsha = 16.5*1e-2, tos = 1750.0 + te0, tnas = 2e2, dkosps = 0.665; //dkosps - äîïîëíèòåëüíûé êîýôôèöèåíò äëÿ ÊÎ ñ ó÷åòîì ïîðèñòîé ñòðóêòóðû;
double *mko, *Th = NULL, *Tg = NULL, *kektp = NULL, *ektpsha = NULL, *ktpvosha = NULL, *vtesha = NULL, tmasha, tmisha, dpcts = 0.314148; //dpcts - äîëÿ ïëîùàäè ïåðåìû÷êè, ÷åðåç êîòîðóþ ïåðåíîñèòñÿ ÷èñòîé òåïëîïðîâîäíîñòüþ ÒÊ
double *alphaSha = NULL, *txsha = NULL, *kxsha = NULL, cop = 0.0, bop = 0.0, tnr = 0.0, bn = 1e-2, bk = 2e0 / pow(1e0 - dpcts, 2e0);
double cn = 1e-2, ck = 4e0, *temrass=NULL, *ooxsha=NULL, sfeosha = 1.24e-2, smgosha = 0.29e-2, salosha = 41.9e-2, ssiosha = 54e-2, *dpctsm;
int vtsh = 0, sctx = 0, dkoscl = 6, vystsha = 1, vybsha = 3;
char *sns = NULL, *sss = NULL, *skpts = NULL, *skptsk = NULL, *svsk = NULL, *svs = NULL, *snms = NULL, *sfnos = NULL;
//----------------------------------------
double *podschchieleSha(int, int, int, double *, double *);
double *izstNSha(int, int, int, int);
double rasotprpovsSha(int *, int *, int, int, int, int, double *, double *);
double otrprovsSha(int, int, double *, double *);
double *kopoSha(double, double, int, int, double, double, double, int, double *);
double opredLuchSostSha(double *, double *, int, int);
double *koefPribSha(double *, double *, int, double *);
double *zadrktSha(int, int, double, int, double, double, int, double, int, int, double *);
double **chaRTASha(int, double *, double *, double *, double *, double *, double *, int);
double **izmRTASha(double *, int, double *, double *, double *, double *, double *, double *, int, int);
double *opredKoefOtr(double *, double *, int, double, int, int, double *, double *, int);
void zadrktShaNac();
void NapMasVozdSha(double *, double *, int);
double *opredKTPTverKarkSha(double *, double *, double, double, double, double, double, double, int, double *, double *, double *, int, int, int);
void opredtemphc(double *, double *, int, int, double);
double opredKTPTKTochSha(double *, double *, double, int);
double *usrednen(double *, double *, int, int);
void vyvodfile(double *, int, int, double, char *);
void napstrsha();
double *reshnewtrafs(double *, double *, double *, double *, int, double *, double *, int, double *, double *, int, double *, double *, int, double, double *, double *, int, double, double, double, double *, int, double, double, double);
double *reshnewrafsokon(double *, double **, double **, double *, int, int, double, double *, double *, int, double, double *, int, double *, int, double, double, double, double, double, double *, double *, double *, int);
void PrintMatr(double **, int);
void osvopam();
void iniarrele(int, double, double, double);
double **opredTempLPStenSha(double *, double *, double *, double *, double, int, double *, double *, double *, double *, int, int, double, double, double, int, char *);
double **RaschVneshIzluchSha(double *, double *, double *, double *, double *, int, double, double, char *);
double **RasLuchPloTepPot(int, double *, double *, double *, double *, double *, double *, int, double *, double *, double *, char *);
double **RaschSobLuchPlotTepPot(int, double *, double *, double *, double *, double *, double *, double, double, double *, int, char *);
double opredUrovPodderM03(double);
double *opredTempStenShaFragm(double *, int, double *, double *, double *, double *, int, int, double, double, double, double, double);
double *KoefPoglRosselNac(double *, int, int, double, double, double, double *, double *, int, double, double, double *, double *, int, int, int);
double LuchKTPChudnovsky(double *, double, int, double);
double epsisredsha(double, double *, double *, int, double *, double *, int);
double **RaschRTASha(int, double, double, double, double, double, int, int, int, int);
double *oprRasTemNach(int, int, double *, double *, int, double *, double, double, double, double, double, int);
double **vybFunRasPorpoRazSha(double, int, int);
double *oprEffDoliTepPeren(double, double, double);
double *KorrZnachVozdPros(double, double, double, int);
double *koefoslab(double, double, double, double *, int, double *);
double vychNevyaz(double **, double **, double *, double *, int);
double *opredPolTempTvKarShaFragm(double *, int, double *, double *, int, double, double, double, double, double);
double *EffectTols(double *, double *, double *, double, double, int);
double SeryeStenkiRasIzl(double, double, double, double *, double *, double *, double *, double *, int *, int);
double oprProcSoderpoPoris(double *, double *, double, int);
double BolTochRasAlpha(int, int, double, double, double, double *, double *, double *, int, int, char *, double *, double *, int, double *, double *, int, double *, double *, double *, double *, double *, double *);
double RasFracXeffSha60(int);
double RaschAlphaTvKarSha();
double F0_lamT(double);
double RasIzlSerStenNac(double *, double *, double *, double *, double *, double *, double *, double, double, double, double, int, double, double, double, double, int, double *, double *, int, int, double *, double *, double *, char *, int, double *, double *, int);
double KorrZnachVozdProsSham(double, double, double);
double *rasMetNewtRafs(double *, double **, double **, double *, double, double, int);
double *FuncRaschIzl(double, double, double, double, int, double *, double, double *, double, double, double, double, int, double *, double *, int, int, char *, double, int, double *, double, double *, double *, int, double *, double *, int, double *, double, double, double *, double *, double *, double *, double *, double *, double *, double *, double *, int, double, double, int, double *, double *, double, double, double, char *, int);
double **PoiskZavVelTemVer(int, double **, int, double *, double *, int);
void zapisvfile(double *, int, char *);
double *poisMasKoefsha(double *, int);
//----------------------------------------
void napstrsha()
{
	sns = new char[ds]; sss = new char[ds]; skpts = new char[2 * ds]; skptsk = new char[ds]; svsk = new char[ds]; svs = new char[2 * ds];
	snms = new char[ds]; sfnos = new char[ds];
	int k; if ((!sns) || (!sss) || (!skpts) || (!skptsk) || (!svsk) || (!svs) || (!snms) || (!sfnos))
	{ cout << "No_memory!" << endl; k = getchar(); exit(1); }
	k = 0;
	sns[k] = 'D'; k++; sns[k] = ':'; k++; sns[k] = '\\'; k++; sns[k] = '\\'; k++; sns[k] = '_';  k++; sns[k] = 'À';  k++;
	sns[k] = 'ñ'; k++; sns[k] = 'ï'; k++; sns[k] = 'è';  k++; sns[k] = 'ð';  k++; sns[k] = 'à';  k++; sns[k] = 'í';  k++;
	sns[k] = 'ò'; k++; sns[k] = 'ó'; k++; sns[k] = 'ð';  k++; sns[k] = 'à';  k++; sns[k] = '\\'; k++; sns[k] = '\\'; k++;
	sns[k] = 't'; k++; sns[k] = 'm'; k++; sns[k] = 'p';  k++; sns[k] = '\\'; k++; sns[k] = '\\'; k++; sns[k] = '\0'; k++;
	k = 0;
	sss[k] = 'C';  k++; sss[k] = ':';  k++; sss[k] = '\\'; k++; sss[k] = '\\'; k++; sss[k] = 'U';  k++; sss[k] = 's';  k++;
	sss[k] = 'e';  k++; sss[k] = 'r';  k++; sss[k] = 's';  k++; sss[k] = '\\'; k++; sss[k] = '\\'; k++; sss[k] = 'À';  k++;
	sss[k] = 'í';  k++; sss[k] = 'ä';  k++; sss[k] = 'ð';  k++; sss[k] = 'å';  k++; sss[k] = 'é';  k++; sss[k] = '\\'; k++;
	sss[k] = '\\'; k++; sss[k] = 'D';  k++; sss[k] = 'o';  k++; sss[k] = 'c';  k++; sss[k] = 'u';  k++; sss[k] = 'm';  k++;
	sss[k] = 'e';  k++; sss[k] = 'n';  k++; sss[k] = 't';  k++; sss[k] = 's';  k++; sss[k] = '\\'; k++; sss[k] = '\\'; k++;
	sss[k] = '_';  k++; sss[k] = 'À';  k++; sss[k] = 'ñ';  k++; sss[k] = 'ï';  k++; sss[k] = 'è';  k++; sss[k] = 'ð';  k++;
	sss[k] = 'à';  k++; sss[k] = 'í';  k++; sss[k] = 'ò';  k++; sss[k] = 'ó';  k++; sss[k] = 'ð';  k++; sss[k] = 'à';  k++;
	sss[k] = '\\'; k++; sss[k] = '\\'; k++; sss[k] = 't';  k++; sss[k] = 'm';  k++; sss[k] = 'p';  k++; sss[k] = '\\'; k++;
	sss[k] = '\\'; k++; sss[k] = '\0';
	k = 0;
	skptsk[k] = 'K'; k++; skptsk[k] = 'o'; k++; skptsk[k] = 'e'; k++; skptsk[k] = 'f'; k++; skptsk[k] = 'f'; k++; skptsk[k] = 'i'; k++;
	skptsk[k] = 'c'; k++; skptsk[k] = 'i'; k++; skptsk[k] = 'e'; k++; skptsk[k] = 'n'; k++; skptsk[k] = 't'; k++; skptsk[k] = '_'; k++;
	skptsk[k] = 'p'; k++; skptsk[k] = 'o'; k++; skptsk[k] = 'g'; k++; skptsk[k] = 'l'; k++; skptsk[k] = 'o'; k++; skptsk[k] = 's'; k++;
	skptsk[k] = 'c'; k++; skptsk[k] = 'h'; k++; skptsk[k] = 'e'; k++; skptsk[k] = 'n'; k++; skptsk[k] = 'i'; k++; skptsk[k] = 'y'; k++;
	skptsk[k] = 'a'; k++; skptsk[k] = '_'; k++; skptsk[k] = 's'; k++; skptsk[k] = 'h'; k++; skptsk[k] = 'a'; k++; skptsk[k] = '_'; k++;
	skptsk[k] = 'T'; k++; skptsk[k] = '.'; k++; skptsk[k] = 't'; k++; skptsk[k] = 'x'; k++; skptsk[k] = 't'; k++; skptsk[k] = '\0';
	k = 0;
	svsk[k] = 'D'; k++; svsk[k] = 'o'; k++; svsk[k] = 'l'; k++; svsk[k] = 'i'; k++; svsk[k] = '_'; k++; svsk[k] = 'p'; k++; svsk[k] = 'r'; k++;
	svsk[k] = 'o'; k++; svsk[k] = 'p'; k++; svsk[k] = '_'; k++; svsk[k] = 'S'; k++; svsk[k] = 'h'; k++; svsk[k] = 'a'; k++; svsk[k] = 'm'; k++;
	svsk[k] = 'o'; k++; svsk[k] = 't'; k++; svsk[k] = '-'; k++; svsk[k] = nf;  k++; svsk[k] = '.'; k++; svsk[k] = 't'; k++; svsk[k] = 'x'; k++;
	svsk[k] = 't'; k++; svsk[k] = '\0';
	k = 0;
	snms[k] = 'N'; k++; snms[k] = 'o'; k++; snms[k] = '_'; k++; snms[k] = 'm'; k++; snms[k] = 'e'; k++; snms[k] = 'm'; k++; snms[k] = 'o'; k++;
	snms[k] = 'r'; k++; snms[k] = 'y'; k++; snms[k] = '!'; k++; snms[k] = '\0';
	k = 0;
	sfnos[k] = 'F'; k++; sfnos[k] = 'i'; k++; sfnos[k] = 'l'; k++; sfnos[k] = 'e'; k++; sfnos[k] = '_'; k++; sfnos[k] = 'i'; k++;
	sfnos[k] = 's'; k++; sfnos[k] = '_'; k++; sfnos[k] = 'n'; k++; sfnos[k] = 'o'; k++; sfnos[k] = 't'; k++; sfnos[k] = '_'; k++;
	sfnos[k] = 'o'; k++; sfnos[k] = 'p'; k++; sfnos[k] = 'e'; k++; sfnos[k] = 'n'; k++; sfnos[k] = '!'; k++; sfnos[k] = '\0';
	strcpy(skpts, sss); strcat(skpts, skptsk); skpts[strlen(skpts) + 1] = '\0';
	strcpy(svs, sss); strcat(svs, svsk); svs[strlen(svs) + 1] = '\0'; /*cout << svs << endl << skpts << endl;*/
}
double *poisMasKoefsha(double *kektp, int n)
{
	double ko = 1e-2, p20 = 2e1*ko, p24 = 24.0*ko, p30 = 3e1*ko, p33 = 33.0*ko, p16 = 16.0*ko, p10 = 1e1*ko; int k=0;
	double s28=28e-2, s38=38e-2, s45=45e-2;
	if (!vrsh) { sfeosha = 1.24*ko; smgosha = 0.29*ko, salosha = 41.9*ko, ssiosha = 54.0*ko; porsha=21.8*ko; } //Ðîó÷êà
	else if (vrsh==1) { sfeosha = 1.21*ko; smgosha = 0.29*ko; salosha = 42.6*ko; ssiosha = 1e0-salosha-sfeosha-smgosha; porsha=11.0144*ko; } //ØÏÄ-41
	else if (vrsh==2) { sfeosha = 1.64*ko; smgosha = 0.36*ko; salosha = 35.9*ko; ssiosha = 59.1e-2;  porsha=25.2*ko; } //ØÁ-1 2-1
	else if (vrsh==3) { sfeosha = 1.66*ko; smgosha = 0.4*ko; salosha = 37.3*ko; ssiosha = 57.4*ko;  porsha=26.5*ko; } //ØÂ-1 1-1
	else if (vrsh==4) { sfeosha = 1.24*ko; smgosha = 0.29*ko; salosha = 41.9*ko; ssiosha = 54*ko;  porsha=11.5*ko; } //ØÏÄ
	else if (vrsh==5) { sfeosha = 1.54*ko; smgosha = 0.3*ko; salosha = 38.6*ko; ssiosha = 56.5*ko;  porsha=16.5*ko; } //ØÊÓ-32 3-1
	for (k=0; k<n; k++) kektp[k]=0.0;
	if ((salosha >= s28) && (salosha <= s38)) {
		if ((porsha >= p20) && (porsha < p24)) { vybsha = 0; vystsha = 0; kektp[3] = -0.435e-9; kektp[2] = 0.685e-6; kektp[1] = 0.134e-3; kektp[0] = 0.725; }
		else if ((porsha >= p24) && (porsha < p30)) { vybsha = 0; vystsha = 1; kektp[3] = -0.867e-9; kektp[2] = 1.77e-6; kektp[1] = -0.523e-3; kektp[0] = 0.806; }  //çàäàíèå êîýôôèöèåíòîâ - øàìîò ñðåäíåé ïîðèñòîñòè
		else if ((porsha >= p16) && (porsha < p20)) { vybsha = 1; kektp[3] = -0.397e-9; kektp[2] = 0.71e-6; kektp[1] = 0.011e-3; kektp[0] = 0.851; } //óïëîòíåííûé øàìîò
		else if ((porsha >= p30) && (porsha <= p33)) { vybsha = 2; kektp[3] = -0.377e-9; kektp[2] = 0.918e-6; kektp[1] = -0.338e-3; kektp[0] = 0.77; }  //íèçêîïëîòíûé øàìîò
		else if ((porsha >= p10) && (porsha<p16)) { vybsha = 3; kektp[3] = 0.0; kektp[2] = -0.607e-6; kektp[1] = 1.14e-3; kektp[0] = 0.641; }
	} //ïîâûøåííîé ïëîòíîñòè øàìîò
	if ((salosha>s38) && (salosha <= s45)) {
		if ((porsha >= p20) && (porsha < p24)) { vybsha = 0; vystsha = 0; kektp[3] = -0.124e-9; kektp[2] = 0.215e-6; kektp[1] = 0.125e-3; kektp[0] = 1.01; }
		else if ((porsha >= p24) && (porsha < p30)) { vybsha = 0; vystsha = 1; kektp[3] = -0.333e-9; kektp[2] = 0.805e-6; kektp[1] = -0.289e-3; kektp[0] = 0.903; } //çàäàíèå êîýôôèöèåíòîâ - øàìîò ñðåäíåé ïîðèñòîñòè
		else if ((porsha >= p16) && (porsha < p20)) { vybsha = 1; kektp[3] = 0.0; kektp[2] = -0.154e-6; kektp[1] = 0.369e-3; kektp[0] = 1.03; } //óïëîòíåííûé øàìîò
		else if ((porsha >= p30) && (porsha < p33)) { vybsha = 2; kektp[3] = -0.377e-9; kektp[2] = 0.918e-6; kektp[1] = -0.338e-3; kektp[0] = 0.77; }  //íèçêîïëîòíûé øàìîò
		else if ((porsha >= p10) && (porsha < p16)) { vybsha = 3; kektp[3] = 0.0; kektp[2] = -0.141e-6; kektp[1] = 0.437e-3; kektp[0] = 1.32; }
	} //ïîâûøåííîé ïëîòíîñòè øàìîò
	return kektp;
}
void iniarrele(int n, double wmg, double wsi, double wal)
{
	int j, k; qob = new double[cem]; tems = new  double[cem]; kttk = new double[cem]; Th = new double[cem]; stchsrsha = new double[cem];
	Tg = new double[cem]; mko = new double[cem]; ektpsha = new double[cem]; etesha = new double[cem]; ecktpsha = new double[cem]; 
	if ((!qob) || (!tems) || (!kttk) || (!Th) || (!Tg) || (!mko) || (!ektpsha) || (!etesha) || (!stchsrsha) || (!ecktpsha))
	{ cout << snms << endl; k = getchar(); exit(1); }
	for (j = 0; j < cem; j++) { qob[j] = 0.0; tems[j] = 0.0; kttk[j] = 0.0; Th[j] = 0.0; stchsrsha[j] = 0.0; Tg[j] = 0.0; mko[j] = 0.0; ektpsha[j] = 0.0;
		etesha[j] = 0.0; ecktpsha[j] = 0.0; }
	etesha[0] = tnas + te0; for (j = 1; j < cem; j++) etesha[j] = etesha[j - 1] + detes;
	dkoscm = new double[dkoscl]; dkosct = new double[dkoscl];
	if ((!dkoscm) || (!dkosct)) { cout << snms << endl; k = getchar(); exit(1); }
	double tnd = 6e2, dtd = 2e2, tm; dkosct[0] = tnd; for (k = 1; k < dkoscl; k++) dkosct[k] = dkosct[k - 1] + dtd;
	k = 0; dkoscm[k] = 8.15; k++; dkoscm[k] = 6.87; k++; dkoscm[k] = 7.55; k++; dkoscm[k] = 14.84; k++; dkoscm[k] = 20.09; k++; dkoscm[k] = 26.3;
	for (k = 0; k < dkoscl; k++) { tm = dkoscm[k] / 1e2; dkoscm[k] = 1e0 - tm; }
	Rsh = new double[ks]; Rash = new double[ks]; Rtsh = new double[ks];
	Tsh = new double[ks]; Tash = new double[ks]; Ttsh = new double[ks];
	Ash = new double[ks]; Aash = new double[ks]; Atsh = new double[ks];
	alphaSha = new double[ks]; Tpct = new double[ks];
	if ((!Rsh) || (!Rash) || (!Rtsh) || (!Tsh) || (!Tash) || (!Ttsh) || (!Ash) || (!Aash) || (!Atsh) || (!alphaSha) || (!Tpct)) { cout << snms << endl; k = getchar(); exit(1); }
	for (j = 0; j < ks; j++) { Rsh[j] = 0.0; Rash[j] = 0.0; Rtsh[j] = 0.0; Tsh[j] = 0.0; Tash[j] = 0.0; Ttsh[j] = 0.0; Ash[j] = 0.0; Aash[j] = 0.0; Atsh[j] = 0.0; alphaSha[j] = 0.0; Tpct[j] = 0.0; }
	txsha = new double[n]; kxsha = new double[n]; lxsha = new double[n]; qxsha = new double[n]; dtxsha = new double[n]; ooxsha = new double[n];
	if ((!txsha) || (!kxsha) || (!lxsha) || (!qxsha) || (!dtxsha) || (!ooxsha)) { cout << snms << endl; k = getchar(); exit(1); }
	for (j = 0; j < n; j++) { txsha[j] = 0.0; kxsha[j] = 0.0; lxsha[j] = 0.0; qxsha[j] = 0.0; dtxsha[j] = 0.0; ooxsha[j] = 0.0; }
	kektp = new double[ceektp]; if (!kektp) { cout << snms << endl; k = getchar(); exit(1); }
	kektp=poisMasKoefsha(kektp, ceektp);
	double s, p; for (k = 0; k < cem; k++) { s = 0.0; p = 0.0; 
	for (j = 0; j < ceektp; j++) { s = s + kektp[j] * pow(etesha[k] - te0, p); p = p + 1.0; } ektpsha[k] = s; }
	tkuscs = new double[dmkooscs]; kuscs = new double[dmkooscs];
	if ((!tkuscs) || (!kuscs)) { cout << snms << endl; k = getchar(); exit(1); }
	tkuscs[0] = tnoscs; for (k = 1; k < dmkooscs; k++) tkuscs[k] = tkuscs[k - 1] + detes;
	kuscs = koefoslab(wmg, wsi, wal, tkuscs, dmkooscs, kuscs);
	for (k = 0; k < cem; k++) { s = epsisredsha(etesha[k], tkuscs, kuscs, dmkooscs, dkosct, dkoscm, dkoscl); stchsrsha[k] = s; }
	kttk = opredKTPTverKarkSha(etesha, ektpsha, porsha, wsi, wal, wmg, tnoscs, dtoscs, dmkooscs, kuscs, tkuscs, stchsrsha, cem, vybsha, vystsha);
	ktpvosha = new double[dmkv]; vtesha = new double[dmkv]; if ((!ktpvosha) || (!vtesha)) { cout << snms << endl; k = getchar(); exit(1); }
	NapMasVozdSha(ktpvosha, vtesha, dmkv); //for (k = 0; k < cem; k++) cout << "te = " << etesha[k] << "\tektp = " << ektpsha[k] << endl;
}
void osvopam()
{
	delete[]Tsh; delete[]Ash; delete[]Rsh; delete[]Tash; delete[]Aash; delete[]Rash; delete[]Ttsh; delete[]Atsh;
	delete[]Rtsh; delete[]alphaSha; delete[]txsha; delete[]kxsha; delete[]lxsha; delete[]qxsha; delete[]dtxsha; 
	delete[]qob; delete[]tems; delete[]stchsrsha; delete[]kttk; delete[]Th; delete[]Tg; delete[]mko; delete[]kektp; 
	delete[]etesha; delete[]ektpsha; delete[]ktpvosha; delete[]vtesha; delete[]ecktpsha; delete[]Tpct; delete[]dkoscm; 
	delete[]dkosct; delete[]kuscs; delete[]tkuscs; delete[]ktr; delete[]sns; delete[]sss, delete[]skpts; delete[]skptsk;
	delete[]svsk; delete[]svs; delete[]snms; delete[]sfnos; delete[]temrass; delete[]ooxsha;
}
void zadrktShaNac()
{
	int j, jk = nxts, jn = nnxts, k, f = 6, q; napstrsha(); iniarrele(jk-jn, smgosha, ssiosha, salosha);
	double dhk = y0sha/fabs(nxtfs-nnxtfs), hnsha = nnxtfs*dhk, hvko = 130e-6;
	double hvh = 1e-6, hvna = 1e-6, p, r, s; dkosps = RaschAlphaTvKarSha(); //dkosps - äîïîëíèòåëüíûé êîýôôèöèåíò äëÿ ÊÎ ñ ó÷åòîì ïîðèñòîé ñòðóêòóðû
	double d = 0.0, *mw = NULL, *po, ko, **mauk=NULL, hf = 1e0, ka, kb, *ras;
	double *srra, *legr, *prgr, marp, srp; for (j = 0; j < ks; j++) d = d + hf; //cout << "Chislo stenok = " << d << endl;
	for (vtsh = vtn; vtsh < cem; vtsh++) { //ïðîáåãàåì ïî òåìïåðàòóðå
		if (vtsh == vtn) {
			mauk=vybFunRasPorpoRazSha(porsha, vrsh, vystsha);
			k=0; ras=mauk[k]; k++; srra=mauk[k]; k++; prgr=mauk[k]; k++; legr=mauk[k]; k++; 
			po=mauk[k]; srp=po[0]; k++; if (po) delete[]po; po=mauk[k]; marp=po[0]; ko=srp; 
			if (po) delete[]po; delete[]mauk; cout << "Sred razm por = " << ko << "\t"; 
			if (ras) delete[]ras; if (srra) delete[]srra; if (legr) delete[]legr; if (prgr) delete[]prgr; 
			r = d; s = ko; po = KorrZnachVozdPros(ko, r, porsha, 0); ko=po[0]; cout << "Korr sred razm por = " << ko << "\t";
			r = d; ko = s; po = KorrZnachVozdPros(ko, r, porsha, 1); p=po[0]; cout << "Dol Plo = " << p << "\t";
			r = d; ko = s; ko = KorrZnachVozdProsSham(ko, r, porsha);
			bk = 2e0 / pow(hf - dpcts, 2e0); hvna = ko; hvko = ko;  }
		else {
			q = jk - jn; ka = (Th[vtsh] - Tg[vtsh]) / y0sha; kb = Tg[vtsh]; hksha = hnsha;
			for (k = 0; k < q; k++) { temrass[k] = kb + ka*hksha; hksha = hksha + dhk; } }
		hvsha = hvna; hsha = hvsha*(hf - porsha) / porsha;
		while (hvsha <= hvko) {
			j = jn; hksha = hnsha; //ïðîáåãàåì ïî ðàçìåðàì ïîð
			while (j < jk) {
				cout << "hk = " << hksha << "\tte = " << etesha[vtsh] << endl; sctx = j-jn; p = d; //ïðîáåãàåì ïî êîîðäèíàòå
				mw = zadrktSha(j, ks, p, vtsh, hsha, hvsha, 1, etesha[vtsh], 0, 0, mw); kxsha[j-jn] = hksha;
				hksha = hksha + dhk; delete[]mw; j++;
			} vyvodfile(lxsha, jk - jn, 0, hvsha, svs); 
			vyvodfile(ooxsha, jk - jn, 2, 0.0, svs); 
			for (j = 0; j < (jk-jn-1); j++) { r = fabs((txsha[j] - txsha[j + 1]) / (kxsha[j + 1] - kxsha[j])); 
			p = fabs(qxsha[j + 1] + qxsha[j]) / 2e0; 
			lxsha[j] = p / r; //cout << "kx = " << kxsha[j] << "\ttx = " << txsha[j] << "\tqx = " << qxsha[j] << "\tlx = " << lxsha[j] << endl; 
			} vyvodfile(lxsha, jk-jn-1, 0, porsha, svs); 
			vyvodfile(qxsha, jk - jn, 2, 0.0, svs); 
			vyvodfile(txsha, jk - jn, 2, 0.0, svs); 
			hvsha = hvsha + hvh;
		}
	}
	osvopam();
}
double *zadrktSha(int zrp, int kost, double d, int vyte, double htk, double hvp, int prod, double tc, int v, int u, double *rta)
{
	int k; double **mu = RaschRTASha(kost, htk, 0.0, 0.0, hvp, tc, 0, 1, 0, 0), *tt = mu[0], *te = new double[kost];
	if (!te) { cout << snms << endl; k = getchar(); exit(1); }
	else for (k = 0; k < kost; k++) te[k] = tt[k];
	if (!u) {
		k = 0; int kst, q = 0, m = 4, b;
		double *prs = new double[m*kost*kost], *pr = new double[m], Er, g, e = tocrassha, t;
		if ((!prs) || (!pr)) { cout << snms << endl; k = getchar(); exit(1); }
		for (k = 0; k < (m*kost*kost); k++) prs[k] = 0.0;
		q = 0; for (kst = 1; kst <= kost; kst++) {
			for (b = 0; b < m; b++) pr[b] = 0.0;
			for (k = 1; k <= kost; k++) {
				pr = izstNSha(k, kst, m, kost);
				for (b = 0; b < m; b++) prs[q + b] = pr[b]; q = q + 4;
			}
		}
		if (prod == 1) Er = opredLuchSostSha(prs, te, q, zrp);
		delete[]te; delete[]pr; delete[]tt; delete[]mu; return prs;
	}
	else { delete[]tt; delete[]mu; return te; }
}
double **chaRTASha(int kost, double *Traa, double *Refa, double *Aba, double *Refb, double *Trab, double *Abb, int v)
{
	int k, f = 9; double **mu = new double*[f]; if (!mu) { cout << snms << endl; k = getchar(); exit(1); }
	for (k = 0; k < kost; k++) {
		if (Traa[k] * Refa[k] >= 1e0) v = 3; if (v == 3) {
			cout << "Ta = " << Traa[k] << "\tRa = " << Refa[k] << endl;
			Abb[k] = Aba[k]; Trab[k] = Traa[k]; Refb[k] = Refa[k];
		}
	}
	if (v < 3) {
		k = kost; double *tmp = new double[k]; if (!tmp) { cout << snms << endl; k = getchar(); exit(1); }
		for (k = 0; k < kost; k++) {
			Abb[k] = (1e0 - Traa[k] + Refa[k] * Traa[k] - Refa[k]); Abb[k] = Abb[k] / (1e0 - Traa[k] * Refa[k]);
			tmp[k] = pow((1e0 - Refa[k])*Traa[k], 2.0)*Refa[k] / (1e0 - pow(Refa[k] * Traa[k], 2e0)) + Refa[k]; Refb[k] = tmp[k];
			Trab[k] = pow(1e0 - Refa[k], 2e0)*Traa[k] / (1e0 - pow(Refa[k] * Traa[k], 2e0));
		} delete[]tmp;
	}
	k = 0; mu[k] = Refa; k++; mu[k] = Traa; k++; mu[k] = Aba; k++; mu[k] = Refb; k++; mu[k] = Trab; k++; mu[k] = Abb; k++;
	return mu;
}
double **izmRTASha(double *tere, int kost, double *Refa, double *Traa, double *Aba, double *Refb, double *Trab, double *Abb, int vy, int izm) //ïîèñê èçìåíåíèÿ ñòåïåíè ÷åðíîòû èëè ïîãëîùåíèÿ
{
	double **mu, ko = 1e0, dkosc; int k, rt = dmkooscs;
	for (k = 0; k < kost; k++) {
		ko = opredKTPTKTochSha(kuscs, tkuscs, tere[k], rt);
		dkosc = opredKTPTKTochSha(dkoscm, dkosct, tere[k], dkoscl);
		if ((ko<0.0) || (ko>1e0) || (dkosc<0.0) || (dkosc>1e0) || (!izm)) { dkosc = 1e0; ko = 1e0; }
		Aba[k] = Aba[k] * ko*dkosc; Traa[k] = 1e0 - Aba[k] - Refa[k]; Abb[k] = Aba[k]; Trab[k] = Traa[k];
	}
	mu = chaRTASha(kost, Traa, Refa, Aba, Refb, Trab, Abb, vy);
	return mu;
} //ïåðåõîä ê ýôôåêòèâíûì çíà÷åíèÿì R, T, A
double *podschchieleSha(int no, int kste, int ocs, double *Ref, double *Tra)
{
	int kol = 0, *ll = new int[N], *kl = new int[N], p, pe = 0, ee, qs = 0, kk = 0, k = 0, j, jj = 1, w, b = 0, bb = 0, gg = 1, *st = new int[N], *ot = new int[N];
	double pp, *na = new double[4], nat = 0.0; struct derevo *prev, *prevv = NULL, *roo, *poir, *poil, *poi, **pruk = new struct derevo*[1], **ceuk = new struct derevo*[2], **unpe = new struct derevo*[N];
	prev = new struct derevo;
	if ((!na) || (!kl) || (!ll) || (!prev) || (!pruk) || (!ceuk) || (!st) || (!ot) || (!unpe)) { cout << snms << endl; p = getchar(); exit(1); }
	for (j = 0; j < 4; j++) na[j] = 0.0;
	kol = 0; kk = kol; prev->lev = gg; gg++; prev->ste = no; prev->vis = 1; prev->next = NULL; roo = prev; kol++; prev->otre = -1; prev->back = NULL; pruk[0] = prev; unpe[b] = prev; b++; kl[k] = kol - kk; k++;
	//-----------
	bb = 2; for (j = 0; j < bb; j++) ceuk[j] = NULL; kk = kol; pe = 0;
	poir = new struct derevo; poil = new struct derevo; if ((!poir) || (!poil)) { cout << snms << endl; j = getchar(); exit(1); }
	poil->back = prev; poil->otre = 0; poir->lev = gg; poil->lev = gg; poir->back = prev; poir->otre = 1; poir->ste = prev->ste + 1; poil->ste = prev->ste - 1;
	poir->vis = 1; if ((poir->ste<1) || (poir->ste>ocs)) poir->vis = 0; if (poir->vis == 1) { ceuk[pe] = poir; kol++; pe++; }
	else delete poir;
	poil->vis = 1; if ((poil->ste<1) || (poil->ste>ocs)) poil->vis = 0; if (poil->vis == 1) { ceuk[pe] = poil; kol++; pe++; }
	else delete poil;
	j = 0; poi = ceuk[j]; prev = unpe[b - 1]; gg++;
	while ((poi) && (j < pe))
	{
		if (poi->vis == 1)
		{
			prev->next = poi;
			prev = poi;
		}
		j++; poi = ceuk[j];
	}
	unpe[b] = prev; b++;
	kl[k] = kol - kk; k++;
	delete[]pruk; pruk = new struct derevo*[pe]; if (!pruk) { cout << snms << endl; j = getchar(); exit(1); }
	qs = 0; for (j = 0; j<pe; j++) { pruk[j] = NULL; poi = ceuk[j]; if ((poi) && (poi->vis == 1)) { pruk[qs] = poi; qs++; } } jj = qs; delete[]ceuk;
	//------------
	//0 - ïðîïóñêàíèå (left), 1 - îòðàæåíèå (right)
	pp = 3.0; for (p = 3; p <= N; p++) {
		w = floor(pow(2.0, pp - 1.0)); bb = 2 * pe; pp = pp + 1.0;
		if (bb>0) { ceuk = new struct derevo*[bb]; if (!ceuk) { cout << snms << endl; j = getchar(); exit(1); } else for (j = 0; j < bb; j++) ceuk[j] = NULL; }
		pe = 0; qs = 0; ee = 0; kk = kol;
		while (ee<w) {
			if ((qs<jj) && (pruk) && (ceuk)) {
				prev = pruk[qs];
				if (prev) {
					prevv = prev->back;
					if (prevv)
					{
						poir = new struct derevo; poil = new struct derevo; if ((!poir) || (!poil)) { cout << snms << endl; j = getchar(); exit(1); }
						poir->back = prev; poir->otre = 1; poil->back = prev; poil->otre = 0; poir->next = NULL; poil->next = NULL; poir->lev = gg; poil->lev = gg;
						if (prev->otre == 1) { if (prevv->ste>prev->ste) { poil->ste = prev->ste - 1; poir->ste = prev->ste + 1; } else { poil->ste = prev->ste + 1; poir->ste = prev->ste - 1; } }
						if (prev->otre == 0) if (prevv->ste>prev->ste) { poil->ste = prev->ste - 1; poir->ste = prev->ste + 1; }
						else { poil->ste = prev->ste + 1; poir->ste = prev->ste - 1; }
						if (prev->otre == -1) if (prevv->ste > prev->ste) { poil->ste = prev->ste - 1; poir->ste = prev->ste + 1; }
						else { poil->ste = prev->ste + 1; poir->ste = prev->ste - 1; }
						poir->vis = 1; if ((poir->ste<1) || (poir->ste>ocs) || (prev->vis == 0)) poir->vis = 0; if (poir->vis == 1) { ceuk[pe] = poir; kol++; pe++; }
						else delete poir;
						poil->vis = 1; if ((poil->ste<1) || (poil->ste>ocs) || (prev->vis == 0)) poil->vis = 0; if (poil->vis == 1) { ceuk[pe] = poil; kol++; pe++; }
						else delete poil;
						ee = ee + 2; qs++;
					}
				}
			} ee++;
		}
		pruk = new struct derevo*[pe]; if (!pruk) { cout << snms << endl; j = getchar(); exit(1); }
		qs = 0; for (j = 0; j < pe; j++) { poi = ceuk[j]; if ((poi) && (poi->vis == 1)) { pruk[qs] = poi; qs++; } } jj = qs;
		kl[k] = kol - kk; k++;
		j = 0; poi = pruk[j]; prev = unpe[b - 1];
		while ((poi) && (j < pe))
		{
			if (poi->vis == 1)
			{
				prev->next = poi; prev = poi;
			}
			j++; poi = pruk[j];
		} unpe[b] = prev; b++; gg++; delete[]ceuk;
	}
	j = 0; for (p = 0; p < N; p++) { j = j + kl[p]; ll[p] = j; }
	//------------------------------
	for (j = 0; j < 4; j++) na[j] = 0.0; bb = 1; poi = roo;
	for (k = 1; k <= N; k++) {
		kk = bb - 1; b = 0;
		while ((b < kl[kk]) && (poi)) {
			if (poi->lev == bb) {
				for (w = 0; w < N; w++) { ot[w] = 0; st[w] = 0; }
				prev = poi;
				for (w = 0; w<bb; w++)
				{
					if (poi) {
						st[kk - w] = poi->ste;
						ot[kk - w] = poi->otre;
						poi = poi->back;
					}
				}
				poi = prev;
				nat = 0.0; nat = rasotprpovsSha(st, ot, kk, kste, no, bb, Ref, Tra);
				if (nat>0) {
					w = 0; //cout << "nat = " << nat << endl; 
					if (st[kk] == kste)
					{
						if (st[kk - 1]<kste) w = 0; else w = 1; if (kste == 1) w = 1; if (kste == ocs) w = 0; na[w] = na[w] + nat;
						w = 2; if (st[1]<no) w = 2; else w = 3; if (no == 1) w = 3; if (no == ocs) w = 2; na[w] = na[w] + nat; //3 - èçëó÷åíèå èäåò âïðàâî îò èçëó÷àþùåé ñòåíêè, 2 - âëåâî
					}
				} //0 - lr (èçëó÷åíèå ïàäàåò íà ðàññìàòðèâàåìóþ ñòåíêó ñëåâà, ò.å. èäåò ñëåâà - íàïðàâî), 1 - rl (èçëó÷åíèå îò äðóãèõ ñòåíîê èäåò ñïðàâà, ò.å. ðàñïðîñòðàíÿåòñÿ ñïðàâà - íàëåâî)
				poi = poi->next; b++;
			}
		} bb++;
	}
	poi = roo; while (poi)  { prev = poi->next; delete poi; poi = prev; }
	delete[]ot; delete[]st; delete[]pruk; delete[]kl; delete[]ll; delete[]unpe; //getchar();
	return na;
}
double rasotprpovsSha(int *stt, int *ott, int gg, int kst, int izlst, int kost, double *R, double *T)
{
	int e = 1, ee = 0, f = 1, w; double po = 1.0, pot;
	if ((stt[gg] == kst) && (kost > 1)) {
		while (e <= gg) {
			w = stt[ee]; if (izlst == stt[0]) { if (f > 0) { e++; ee++; f = 0; continue; } }
			pot = otrprovsSha(w - 1, ott[e], R, T);
			po = po*pot; ee++; e++;
		}
	}
	else po = 0.0; return po;
}
double otrprovsSha(int ste, int otr, double *R, double *T)
{
	double ko = 1e0;
	if (otr == 1) { ko = ko*R[ste]; }
	else if (!otr) { ko = ko*T[ste]; }
	return ko;
}
double *izstNSha(int izst, int kst, int m, int ochs)
{
	int k; double *o;
	if (abs(izst - kst) <= N) o = podschchieleSha(izst, kst, ochs, Rsh, Tsh);
	else {
		o = new double[m]; if (!o) { cout << snms << endl; k = getchar(); exit(1); }
		for (k = 0; k < m; k++) o[k] = 0.0;
	}
	return o;
}
double *kopoSha(double kta, double ktb, int vyb, int kost, double htk, double hvp, double tl, int w, double *al)
{
	int k, q = 100, j, r, f;
	double t0 = 2e1, te = t0 + te0, dte = 1e0, ts = 0.0, t, *p=NULL, a1, a2, t1, t2;
	char *s = new char[q]; KoePog *kp = new KoePog, *ne=NULL, *roo=NULL, *pre=NULL;
	if ((!kp) || (!s)) { cout << snms << endl; j = getchar(); exit(1); } for (j = 0; j < q; j++) s[j] = '\0';
	ifstream fin; fin.open(skpts); if (!fin.is_open()) { cout << sfnos << endl; j = getchar(); exit(1); }
	roo = kp; k = 0; while (!fin.eof()) {
		fin.getline(s, q, '\n');
		ne = new KoePog; if (!ne) { cout << snms << endl; j = getchar(); exit(1); }
		kp->alp = atof(s)*dkoals*dkosps; kp->tem = te; kp->nex = ne; pre = kp; kp = ne; k++; te = te + dte; kp->nex = NULL;
	}
	delete[]ne; kp = NULL; pre->nex = kp; fin.close(); delete[]s; r = k; //cout << "r = " << r << "\tvyb = " << vyb << endl;
	if ((!vyb) || (vyb == 2)) {
		f = 2; double *xi = new double[kost], *teks = new double[kost], *koe = new double[f], knat;
		if ((!teks) || (!koe) || (!xi)) { cout << snms << endl; j = getchar(); exit(1); }
		teks = oprRasTemNach(cem, ceektp, teks, koe, kost, xi, htk, hvp, hksha, kta, ktb, w);
		for (k = 0; k < kost; k++) {
			kp = roo->nex; pre = roo; j = 0; t = teks[k];
			while ((kp) && (j<r)) {
				if (kp->tem>t)
				{
					a1 = pre->alp; a2 = kp->alp; t1 = pre->tem; t2 = kp->tem; knat = (a2 - a1) / (t2 - t1); al[k] = a1 + knat*(t - t1); break;
				}
				else { pre = kp; kp = kp->nex; } j++;
			}
		} delete[]xi; delete[]koe;
		if (vyb == 2) { p = al; delete[]teks; }
		else p = teks;
	}
	if (vyb == 1) {
		kp = roo->nex; j = 0; pre = roo; t = 0.0;
		while ((kp) && (j<r)) {
			if (kp->tem>tl)
			{
				a1 = pre->alp; a2 = kp->alp; t1 = pre->tem; t2 = kp->tem; t = a1 + (a2 - a1)*(tl - t1) / (t2 - t1); break;
			}
			else { pre = kp; kp = kp->nex; } j++;
		} j = 1; p = new double[j];
		if (p) p[0] = t; else { cout << snms << endl; j = getchar(); exit(1); }
	}
	kp = roo; while (kp) { ne = kp->nex; delete kp; kp = ne; } //óäàëåíèå ñïèñêà
	return p;
}
double *koefPribSha(double *ktp, double *te, int le, double *ko)
{
	int k, kem = 3; double **A = new double*[kem], *AA, *b = new double[kem], yx2 = 0.0, yx = 0.0, p, hf = 1e0;
	double x4 = 0.0, x3 = 0.0, x2 = 0.0, x = 0.0, y = 0.0, de = 0.0, de1 = 0.0, de2 = 0.0, de3 = 0.0;
	if (A) { for (k = 0; k < kem; k++) { AA = new double[kem]; if (AA) A[k] = AA; else { cout << snms << endl; k = getchar(); exit(1); } } }
	else { cout << snms << endl; k = getchar(); exit(1); }
	if ((!ko) || (!b)) { cout << snms << endl; k = getchar(); exit(1); }
	for (k = 0; k < le; k++) {
		yx2 = yx2 + ktp[k] * pow(te[k], 2e0); yx = yx + ktp[k] * te[k]; y = y + ktp[k];
		x4 = x4 + pow(te[k], 4e0); x3 = x3 + pow(te[k], 3e0); x2 = x2 + pow(te[k], 2e0); x = x + te[k];
	}
	b[0] = yx2; b[1] = yx; b[2] = y; p = 0.0; for (k = 0; k < le; k++) p = p + hf;
	A[0][0] = x4; A[0][1] = x3; A[0][2] = x2; A[1][0] = x3; A[1][1] = x2; A[1][2] = x; A[2][0] = x2; A[2][1] = x; A[2][2] = p;
	de = A[0][0] * (A[2][2] * A[1][1] - A[2][1] * A[1][2]) - A[0][1] * (A[1][0] * A[2][2] - A[2][0] * A[1][2]) + A[0][2] * (A[1][0] * A[2][1] - A[2][0] * A[1][1]);
	de1 = b[0] * (A[1][1] * A[2][2] - A[2][1] * A[1][2]) - A[0][1] * (b[1] * A[2][2] - b[2] * A[1][2]) + A[0][2] * (b[1] * A[2][1] - b[2] * A[1][1]);
	de2 = A[0][0] * (b[1] * A[2][2] - b[2] * A[1][2]) - b[0] * (A[1][0] * A[2][2] - A[2][0] * A[1][2]) + A[0][2] * (A[1][0] * b[2] - A[2][0] * b[1]);
	de3 = A[0][0] * (A[1][1] * b[2] - A[2][1] * b[1]) - A[0][1] * (A[1][0] * b[2] - A[2][0] * b[1]) + b[0] * (A[1][0] * A[2][1] - A[2][0] * A[1][1]);
	ko[2] = de1 / de; ko[1] = de2 / de; ko[0] = de3 / de;
	delete[]b; for (k = 0; k < kem; k++) { AA = A[k]; delete[]AA; } return ko;
}
void NapMasVozdSha(double *ktpvoz, double *tvoz, int dmvo)
{
	int k = 0, dlma = dmvo;
	ktpvoz[k] = 2.44; k++; ktpvoz[k] = 2.51; k++; ktpvoz[k] = 2.59; k++; ktpvoz[k] = 2.67; k++; ktpvoz[k] = 2.76; k++; ktpvoz[k] = 2.83; k++;
	ktpvoz[k] = 2.90; k++; ktpvoz[k] = 2.96; k++; ktpvoz[k] = 3.05; k++; ktpvoz[k] = 3.13; k++; ktpvoz[k] = 3.21; k++; ktpvoz[k] = 3.34; k++;
	ktpvoz[k] = 3.49; k++; ktpvoz[k] = 3.64; k++; ktpvoz[k] = 3.78; k++; ktpvoz[k] = 3.93; k++; ktpvoz[k] = 4.27; k++; ktpvoz[k] = 4.60; k++;
	ktpvoz[k] = 4.91; k++; ktpvoz[k] = 5.21; k++; ktpvoz[k] = 5.74; k++; ktpvoz[k] = 6.22; k++; ktpvoz[k] = 6.71; k++; ktpvoz[k] = 7.18; k++;
	ktpvoz[k] = 7.63; k++; ktpvoz[k] = 8.07; k++; ktpvoz[k] = 8.50; k++; ktpvoz[k] = 9.15;
	for (k = 0; k < dlma; k++) ktpvoz[k] = ktpvoz[k] / 1e2; //ÊÒÏ âîçäóõà
	k = 0;
	tvoz[k] = 0.0; k++; tvoz[k] = 1e1; k++; tvoz[k] = 2e1; k++; tvoz[k] = 3e1; k++; tvoz[k] = 4e1; k++; tvoz[k] = 5e1; k++;
	tvoz[k] = 6e1; k++; tvoz[k] = 7e1; k++; tvoz[k] = 8e1; k++; tvoz[k] = 9e1; k++; tvoz[k] = 1e2; k++; tvoz[k] = 12e1; k++;
	tvoz[k] = 14e1; k++; tvoz[k] = 16e1; k++; tvoz[k] = 18e1; k++; tvoz[k] = 2e2; k++; tvoz[k] = 25e1; k++; tvoz[k] = 3e2; k++;
	tvoz[k] = 35e1; k++; tvoz[k] = 4e2; k++; tvoz[k] = 5e2; k++; tvoz[k] = 6e2; k++; tvoz[k] = 7e2; k++; tvoz[k] = 8e2; k++;
	tvoz[k] = 9e2; k++; tvoz[k] = 1e3; k++; tvoz[k] = 11e2; k++; tvoz[k] = 12e2;
	for (k = 0; k < dlma; k++) tvoz[k] = tvoz[k] + te0; //òåìïåðàòóðû, ïðè êîòîðûõ îïðåäåëÿåòñÿ ÊÒÏ âîçäóõà
}
double opredLuchSostSha(double *prot, double *Tsr, int le, int zf)
{
	int k = 0, j = 0, q = 0, m = 0, l = 3, mma = 30000, mm, mt=0, vy = 9, idr=0;
	double **mauk, *pt, s = 0.0, r = 0.0, p = 0.0, de=1e0, rez=0.0, rap=0.0;
	double *ao = new double[2 * N], *po = NULL, d = 0.0, hb = 1e-1, hb0 = hb, hf = 1e0; 
	for (j = 0; j < ks; j++) d = d + hf;
	double ta = 0.0, tb = 0.0, tc = 0.0, fa = 0.0, fb = 0.0, fc = 0.0;
	double ba = bn, bb = bk, bc = (ba + bb) / 2e0, xk=0.0, dxk=1e-3;
	double ca = cn, cb = ck, cc = (ca + cb) / 2e0, hc = 1e-1, hc0 = hc, tt=0.0;
	double mk = 1e2, mkm=mk, c00, b0 = bc, c0 = cc, kdc = 5e0, kdb = 5e0, tminsha, tmaxsha;
	if (!ao) { cout << snms << endl; k = getchar(); exit(1); } for (k = 0; k < (2 * N); k++) ao[k] = 0.0;
	qobsha = opredKTPTKTochSha(qob, etesha, etesha[vtsh], cem);
	cout << "qo = " << qobsha << "\tdscp = " << dpcts << "\t";
	if ((vtsh == vtn) && (sctx <= 2) && (!temrass)) {
		j = nxts - nnxts; temrass = new double[j];
		if (!temrass) { cout << snms << endl; k = getchar(); exit(1); }
		ta = Th[vtsh] - Tg[vtsh]; ta = ta / y0sha; tb = Tg[vtsh];
		for (k = 0; k < j; k++) { temrass[k] = tb + ta*xk; xk = xk + dxk; }
	}
	if ((vtsh == vtn) && (sctx<=2) && (!ktr)) {
			ktr = KoefPoglRosselNac(etesha, idr, cem, smgosha, ssiosha - pksvs, salosha + pksvs, dkoscm, dkosct, dkoscl, dkosps, dkoals, kuscs, tkuscs, dmkooscs, 0, 0);
			for (k = 0; k < cem; k++) cout << ktr[k] << "\t";
	}
		l = vtsh; tminsha = Th[l]; tmaxsha = Tg[l];
		ta = tminsha; tb = tmaxsha; tc = temrass[sctx];
		mauk = RaschRTASha(ks, hsha, 0.0, 0.0, hvsha, tc, 0, 0, 0, 1);
		k = 0; Rash = mauk[k]; k++; Tash = mauk[k]; k++; Aash = mauk[k]; k++; Rsh = mauk[k]; k++; Tsh = mauk[k]; k++;
		Ash = mauk[k]; k++; Rtsh = mauk[k]; k++; Ttsh = mauk[k]; k++; Atsh = mauk[k]; delete[]mauk;
				ca = cn; cb = ck; m = 0; q = 0;
				while ((m<mma) && (fabs(cb - ca)>1e-3) && (!q))
				{
					dpcts=opredKTPTKTochSha(dpctsm, etesha, tc, cem);
					cc = (ca + cb) / 2e0;
					pt = FuncRaschIzl(ta, tb, d, tc, m, prot, de, ao, rez, rap, bc, cc, vy, qob, etesha, cem, 0, snms, dpcts, vtsh, ektpsha, y0sha, ktr, kttk, ks, ktpvosha, vtesha, dmkv, ecktpsha, hsha, hvsha, Rsh, Tsh, Ash, Rtsh, Ttsh, Atsh, txsha, qxsha, dtxsha, sctx, tocrassha, porsha, 2 * N, stchsrsha, Tpct, b0, c0, mk, svs, 0);
					k = 3; fc = pt[k]; delete[]pt;
					if (fabs(fc) < 1e0) { c0 = cc; break; }
					pt = FuncRaschIzl(ta, tb, d, tc, m, prot, de, ao, rez, rap, bc, ca, vy, qob, etesha, cem, 0, snms, dpcts, vtsh, ektpsha, y0sha, ktr, kttk, ks, ktpvosha, vtesha, dmkv, ecktpsha, hsha, hvsha, Rsh, Tsh, Ash, Rtsh, Ttsh, Atsh, txsha, qxsha, dtxsha, sctx, tocrassha, porsha, 2 * N, stchsrsha, Tpct, b0, c0, mk, svs, 0);
					k = 3; fa = pt[k]; delete[]pt;
					if (fabs(fa) < 1e0) { c0 = ca; break; }
					pt = FuncRaschIzl(ta, tb, d, tc, m, prot, de, ao, rez, rap, bc, cb, vy, qob, etesha, cem, 0, snms, dpcts, vtsh, ektpsha, y0sha, ktr, kttk, ks, ktpvosha, vtesha, dmkv, ecktpsha, hsha, hvsha, Rsh, Tsh, Ash, Rtsh, Ttsh, Atsh, txsha, qxsha, dtxsha, sctx, tocrassha, porsha, 2 * N, stchsrsha, Tpct, b0, c0, mk, svs, 0);
					k = 3; fb = pt[k]; delete[]pt;
					if (fabs(fb) < 1e0) { c0 = cb; break; }
					if ((fa*fc) < 0.0) { cb = cc; q = 0; }
					if ((fb*fc) < 0.0) { ca = cc; q = 0; }
					if (((fb*fc)<0.0) && ((fa*fc)<0.0)) { cb = cc; q = 0; }
					if (((fb*fc)>0.0) && ((fa*fc)>0.0)) { q = 1; break; }
					m++;
				}
				c0 = cc; c00 = c0; cop = c00; //cout << "c0 = " << c0 << "\ttb = " << tb << "\ttc = " << tc;
		m = 0; ba = bn; bb = bk; l = vtsh; ta = Th[l]; tb = Tg[l]; tc = temrass[sctx];
		while ((m<mma) && ((bb - ba)>1e-1))
			{
				bc = (ba + bb) / 2e0; b0 = bc; c0 = c00; cc = c0; dpcts=opredKTPTKTochSha(dpctsm, etesha, tc, cem);
				pt = FuncRaschIzl(ta, tb, d, tc, m, prot, de, ao, rez, rap, bc, c0, vy, qob, etesha, cem, 0, snms, dpcts, vtsh, ektpsha, y0sha, ktr, kttk, ks, ktpvosha, vtesha, dmkv, ecktpsha, hsha, hvsha, Rsh, Tsh, Ash, Rtsh, Ttsh, Atsh, txsha, qxsha, dtxsha, sctx, tocrassha, porsha, 2 * N, stchsrsha, Tpct, b0, c0, mk, svs, 0);
				k = 9; s = pt[k]; k = 7; mk = pt[k]; k = 5; b0 = pt[k]; k = 4; tt = pt[k]; k = 10; r = pt[k]; delete[]pt;
				if ((mk < mkm) && (mk>0.0)) { mkm = mk; bop = bc; b0 = bc; lxsha[sctx] = r; ooxsha[sctx] = s; txsha[sctx] = tt; qxsha[sctx] = qobsha; } //cout << "\tbc = " << bc << "\tmk = " << mk << "\tmkm = " << mkm << endl;
				m++; if (bc < 1e0) hb = hb0 / kdb; else hb = hb0; bb = bb - hb;
			} //cout << "\tbop = " << bop << "\tmop = " << mkm << "\tcop = " << cop << "\t";
		if (fabs(tnr - tt) > 1e-1) 
			tnr = tt; else {  
				cn = cop - hc0; if (cn <= 0.0) cn = 1e-2;
				ck = cop + 2e0*hc0;
		bn = bop - hb0; if (bn <= 0.0) bn = 1e-2;
		bk = bop + 2e0*hb0; 
		tnr = tt;
 } 
		delete[]ao; return rez;
}
double *FuncRaschIzl(double ta, double tb, double d, double tc, int m, double *prot, double de, double *ao, double rez, double rap, double b, double c, int vybo, double *qobve, double *eteve, int cemve, int vyve, char *snm, double dpct, int vyte, double *ektpve, double y0ve, double *ktrve, double *kttkve, int kost, double *ktpvove, double *vteve, int dmkvove, double *ecktpve, double htch, double hvoz, double *Refe, double *Trae, double *Abse, double *Reft, double *Trat, double *Abst, double *txve, double *qxve, double *dtxve, int sctve, double tocrasve, double poristost, int dmao, double *stchsrve, double *Tpctve, double b0, double c0, double mk, char *navyfa, int fla)
{
	int j, zf = 1, cels = 6, k, nvm = 11, ksu = 2 * kost, nfm = 28;
	double qrr = 0.0, qr = 0.0, gtm = 0.0, dtma = 0.0, t = 0.0, hlr0 = 0.0, hrl0 = 0.0, rhlr0 = 0.0, slr = 0.0, srl = 0.0, ra10, **mu, ra9, ra, ra7;
	double *Ts = NULL, *Tss = NULL, *sislr = NULL, *sisrl = NULL, *Tna = NULL, *reiz = NULL, *hrl1 = NULL, *hlr1 = NULL, *Tsr = NULL, qis;
	double *fm = new double[nfm], ktptk, ecktp, ktpr, dp = (1e0 - dpct), qs, *tevy = NULL, r, tesr, dote, p, *vm = new double[nvm];
	double qobvee, gg, ep = tocrasve, rr, ra0, tcc=(ta+tb)/2e0, *Evsv=NULL;
	if (!vm) { cout << snm << endl; k = getchar(); exit(1); }
	gtm = LuchKTPChudnovsky(Abse, tc, kost, hvoz); //ïî ×óäíîâñêîìó
	qobvee = opredKTPTKTochSha(qobve, eteve, tc, cemve); if (qobvee <= 0.0) qobvee = opredKTPTKTochSha(qobve, eteve, eteve[vyte], cemve);
	qs = dp*qobvee;
	p = opredKTPTKTochSha(ektpve, eteve, tc, cemve);
	dtma = fabs(tb - ta);
	gtm = dtma / y0ve;
	ktpr = opredKTPTKTochSha(ktrve, eteve, tc, cemve);
	qr = ktpr*gtm; qrr = qr;
	ktptk = opredKTPTKTochSha(kttkve, eteve, tc, cemve);
	ecktp = opredKTPTKTochSha(ecktpve, eteve, tc, cemve);
	if (!m) { t = (dpct*ecktp*b + (1e0 - dp*b)*ktptk); if (fabs(t) > ep) hlr0 = qs*ktpr / t; else hlr0 = 0.0; }
	else hlr0 = rez; hrl0 = 0.0; rhlr0 = hlr0 - hrl0;
	if (qs<rhlr0) { rhlr0 = qs; hlr0 = rhlr0 + hrl0; }
	mu = opredTempLPStenSha(Ts, Tss, Tsr, Tna, tc, ksu, ktpvove, vteve, eteve, kttkve, cemve, dmkvove, htch, hvoz, qs - rhlr0, kost, snm);
	k = 0; Ts = mu[k]; k++; Tss = mu[k]; k++; Tsr = mu[k]; k++; Tna = mu[k]; delete[]mu;
	mu = RaschVneshIzluchSha(Trae, Refe, prot, hlr1, hrl1, ks, hlr0, hrl0, snms);
	k = 0; hlr1 = mu[k]; k++; hrl1 = mu[k]; k++; reiz = mu[k]; slr = reiz[0]; srl = reiz[1]; ra0 = slr - srl; delete[]mu;
	tevy = reshnewtrafs(prot, Tna, hlr1, hrl1, zf, Trae, Abse, kost, kttkve, eteve, cemve, ktpvove, vteve, dmkvove, qs, txve, qxve, sctve, htch, hvoz, tocrasve, ektpve, cels + 2 * kost, tb, ta, y0ve);
	tesr = tevy[2]; txve[sctve] = tesr; qxve[sctve] = tevy[1]; dtxve[sctve] = tevy[0]; gtm = tevy[4];
	if ((m>0) && (fabs(tevy[4]) > 0.0)) r = tevy[1] * b*dp / tevy[4] + opredKTPTKTochSha(kttkve, eteve, tesr, cemve)*(1e0 - b*dp); else r = 0.0; dote = tevy[5]; delete[]tevy;
	if (r<0.0) r = 0.0; if (fabs(p) > ep) gg = fabs((r - p) / p)*1e2; else gg = mk; if (mk < gg) { b0 = b; c0 = c; mk = gg; }
	for (j = 0; j < dmao; j++) ao[j] = 0.0;
	mu = RaschSobLuchPlotTepPot(kost, prot, Ts, Tss, Trae, Refe, Abse, slr, srl, ao, 0, snm); 
	k = 0; ao = mu[k]; k++; sislr = mu[k]; k++; sisrl = mu[k]; delete[]mu;
	mu = RasLuchPloTepPot(kost, hrl1, hlr1, ao, Trae, Refe, Abse, 2, sislr, sisrl, Tsr, snm); 
	k = 0; ao = mu[k]; k++; delete[]reiz; reiz = mu[k]; k++; Evsv=mu[k]; delete[]mu; 
	k = 0; slr = ao[k]; k++; srl = ao[k]; ra = slr - srl;
	qr = RasIzlSerStenNac(Refe, Trae, Abse, prot, Reft, Trat, Abst, tc, hlr0, hrl0, b, vyve, poristost, dpct, htch, hvoz, kost, eteve, kttkve, cemve, vyte, qobve, ktpvove, vteve, snm, dmao, stchsrve, Tpctve, dmkvove); qis = qr; //0 - øàìîò, 1 - âåðìèêóëèò, 2 - ÈÒÎÌ
	qr = (qr*(d - 1e0) + ra)*dp*b / d;
	k = 7; ra7 = (ra + ao[k] * (d - 1e0)) / d; ra7 = ra7*dp*c*b; //ra7=qrr+ra7; 
	k = 9; ra9 = (ra + ao[k] * (d - 1e0)) / d; ra9 = ra9*dp*c*b; //ra9=ra9+qrr; //c - ïîïðàâêà íà ðàçðåøàþùèå óãëîâûå êîýôôèöèåíòû èç-çà íåáåñêîíå÷íîñòè ñòåíîê, b - èõ àñïåêòíîå ñîîòíîøåíèå (ïîïðàâêà íà èõ íåêóáè÷íîñòü)
	k = 10; ra10 = (ra + ao[k] * (d - 1e0)) / d; ra10 = ra10*dp*c*b; //ra10=qrr+ra10; 
	rez = ra; t = opredKTPTKTochSha(kttkve, eteve, tc, cemve); 
	if (fabs(p) > ep) gg = fabs((r - p) / p)*1e2; else gg = mk; if (mk>gg) { b0 = b; c0 = c; mk = gg; }
	if (fabs(qr) > ep) rr = ra9/qr; else rr = 0.0;
	k = 0; fm[k] = rr; k++; fm[k] = dote;     k++; fm[k] = qr;      k++; fm[k] = qrr;      k++; fm[k] = r;         k++; fm[k] = gg;    k++;
	fm[k] = b;         k++; fm[k] = c;        k++; fm[k] = qis;     k++; fm[k] = ao[5];    k++; fm[k] = ao[7];     k++; fm[k] = ao[9]; k++;
	fm[k] = ao[10];    k++; fm[k] = qobvee;   k++; fm[k] = rap;     k++; fm[k] = t;        k++; fm[k] = ra9;       k++; fm[k] = ra10;  k++;
	fm[k] = ta;        k++; fm[k] = tb;       k++; fm[k] = ra0;	    k++; fm[k] = ra9 - qr; k++; fm[k] = ra10 - qr; k++; fm[k] = ra7;   k++; 
	fm[k] = ra7 - qr;  k++; fm[k] = ra;       k++; fm[k] = hksha;   k++; fm[k] = tcc;	   k++;
	if (fla) { vyvodfile(fm, nfm, 2, 0.0, navyfa); //cout << "tc = " << tc << "\ttNR = " << dote << "\tqr = " << qr << "\tqrr = " << qrr; cout << "\tktp = " << r << "\topktp = " << gg << "\tb = " << b << "\tc = " << c << "\tqss = " << qis; cout << "\tao5 = " << ao[5] << "\tao7 = " << ao[7] << "\tao9 = " << ao[9] << "\tao10 = " << ao[10] << "\tqob = " << qobvee; cout << "\trap = " << rap << "\tktp_tk = " << t << "\tra9 = " << ra9 << "\tra10 = " << ra10; cout << "\tta = " << ta << "\ttb = " << tb << "\tslr-srl = " << slr - srl << "\tra9-qr = " << (ra9 - qr) << "\tra10-qr = " << ra10 - qr << endl; 
	} delete[]fm; delete[]sislr; delete[]sisrl; delete[]hlr1; delete[]hrl1; 
	delete[]reiz; delete[]Tsr; delete[]Ts; delete[]Tss; delete[]Tna; delete []Evsv;
	k = 0; vm[k] = ra; k++; vm[k] = qr; k++; vm[k] = qrr; k++; vm[k] = ra9 - qr; k++; vm[k] = dote; k++; 
	vm[k] = b0; k++; vm[k] = c0; k++; vm[k] = mk; k++; vm[k] = rr; k++; vm[k] = gg; k++; vm[k] = r; return vm;
}
double *usrednen(double *ao, double *usr, int sao, int kost)
{
	double s = 0.0, k = 0.0, minz = tocrassha, hf = 1e0; int j;
	for (j = 0; j<kost; j++) if (fabs(usr[j])>minz) { s = s + usr[j]; k = k + hf; }
	s = s / k; ao[sao] = s; //ñðåäíÿÿ âåëè÷èíà
	return ao;
}
double *reshnewtrafs(double *w, double *te, double *hlr, double *hrl, int zf, double *Tm, double *Am, int kost, double *ktptc, double *ete, int chel, double *ktpvo, double *tvo, int dmkvo, double qc, double *tx, double *qx, int scx, double htk, double hvo, double tora, double *laefm, int koelvyma, double tmax, double tmin, double tolob)
{
	int k, j = 0, q, p = 0, dm = 2 * kost, m = 0; double **m1 = new double*[dm], **m4 = new double*[dm], *te2 = new double[dm], *vykh;
	double sig = 5.67e-8, lav, latk, laef, t, wo, wr, wt, w0, w1, w2, w3, *t1, *t4, s, *ssc = new double[dm];
	if ((!m1) || (!m4) || (!ssc) || (!te2)) { cout << snms << endl; k = getchar(); exit(1); }
	for (k = 0; k < dm; k++) te2[k] = te[j];
	p = 0; for (k = 0; k<dm; k++) {
		q = 0;  //k - íîìåðà ñòåíîê äëÿ ðàñ÷åò òåìïåðàòóð, øòðèõ - ñëåâà, äâà øòðèõà - ñïðàâà
		t1 = new double[dm]; t4 = new double[dm]; if ((!t1) || (!t4)) { cout << snms << endl; q = getchar(); exit(1); }
		if (k>0) p = p + ((k + 1) % 2); //cout << "p = " << p << endl;
		for (j = 0; j<dm; j++) { t1[j] = 0.0; t4[j] = 0.0; }
		s = 0.0; j = 0; m = 0;
		while (j<dm) {
			if (j>0) m = m + ((j + 1) % 2); //cout << "m = " << m << "\t"; //2 - èçëó÷åíèå ïîøëî âëåâî îò èçëó÷àþùåé ñòåíêè, çíàê ìèíóñ, 3 - âïðàâî, çíàê ïëþñ
			w0 = w[q]; w1 = w[q + 1]; w2 = w[q + 2]; w3 = w[q + 3]; wo = w2 + w3; //cout << "w0 = " << w0 << "\tw1 = " << w1 << "\tw2 = " << w2 << "\tw3 = " << w3 << endl;
			if (!(k % 2)) wr = w0 - w1*Tm[p]; else wr = w0*Tm[p] - w1;
			if (fabs(wo)>0.0) wt = Am[m] * wr*sig / wo; else wt = 0.0;
			if (!(j % 2)) { wt = wt*w2; }
			else { wt = wt*w3; } t4[j] = wt;
			if (fabs(wo) > 0.0) {
				s = s + wr*(w2 + w3)*(hlr[m] - hrl[m]) / wo; //cout << "wr = " << wr << "\tw2 = " << w2 << "\tw3 = " << w3 << "\thlr = " << hlr[m] << "\t"; 
			} if (j == k) {
				t = te[m]; latk = opredKTPTKTochSha(ktptc, ete, t, chel);
				lav = opredKTPTKTochSha(ktpvo, tvo, t, dmkvo); //1 - èçëó÷åíèå ïðèõîäèò ñëåâà íà êîíå÷íóþ ñòåíêó, çíàê ïëþñ, 0 - ñïðàâà, çíàê ìèíóñ
				if (!j) { t1[j] = latk / htk; t1[j + 1] = -t1[j]; }
				else if (j == (dm - 1)) { t1[dm - 2] = latk / htk; t1[dm - 1] = -t1[dm - 2]; }
				else if (!(j % 2)) { t1[j - 1] = lav / hvo; t1[j] = latk / htk - lav / hvo; t1[j + 1] = -latk / htk; }
				else { t1[j - 1] = latk / htk; t1[j] = lav / hvo - latk / htk; t1[j + 1] = -lav / hvo; }
			}
			if (j > 0) q = q + 4 * ((j - 1) % 2); j++;
		}
		ssc[k] = -s; m1[k] = t1; m4[k] = t4;
	} //cout << "m1 = " << endl; PrintMatr(m1,dm); //cout << "m4 = " << endl; PrintMatr(m4,dm); for (j=0; j<dm; j++) cout << "ssc (" << j << ") = " << ssc[j] << "\t" << "te (" << j << ") = " << te2[j] << "\t"; cout << endl; 
	vykh = reshnewrafsokon(te2, m1, m4, ssc, zf, dm, qc, tx, qx, scx, tora, laefm, chel, ete, koelvyma, tmax, tmin, tolob, htk, hvo, ktptc, ktpvo, tvo, dmkvo);
	for (k = 0; k < dm; k++) { t1 = m1[k]; delete[]t1; } delete[]m1;
	for (k = 0; k < dm; k++) { t4 = m4[k]; delete[]t4; } delete[]m4;
	delete[]ssc; delete[]te2; return vykh;
}
double *reshnewrafsokon(double *te, double **ms1, double **ms4, double *ssc, int zf, int ksu, double qc, double *tx, double *qx, int scx, double tora, double *laefm, int chis, double *ete, int koelvyma, double tmax, double tmin, double tolob, double htch, double hvozd, double *ktptk, double *ktpvo, double *vte, int dmv)
{ //cout << "Newton-Rafsons is on" << endl;
	int qk = 1, k, q, j=10, p, f=4; for (p=0; p<f; p++) qk=qk*j;
	double *mvyz = new double[koelvyma], ta = tmin, tb = tmax, tc, ep=1e-6;
	double *tet = new double[ksu], ksuf = 0.0, ht=1e0, tempplav=18e2;
	double fa, fb, fc, tmaa, tmab, e = 1e1, ra = 1e3, t, r, eps=1e-10;
	if ((!mvyz) || (!tet)) { cout << snms << endl; k = getchar(); exit(1); }
	for (k = 0; k < ksu; k++) { tet[k] = te[k]; ksuf = ksuf + ht; }
	tet = rasMetNewtRafs(tet, ms1, ms4, ssc, ksuf, tora, ksu);
	for (k=0; k<ksu; k++) { if ((tet[k]<ta) || (tet[k]>tb)) tet[k]=0.0; } //zapisvfile(tet, ksu, "C:\\Users\\Àíäðåé\\Documents\\_Àñïèðàíòóðà\\tmp\\2022\\Temp_Stenok.txt"); zapisvfile(ssc, ksu, "C:\\Users\\Àíäðåé\\Documents\\_Àñïèðàíòóðà\\tmp\\2022\\Svob_ch.txt"); for (k=0; k<ksu; k++) zapisvfile(ms1[k], ksu, "C:\\Users\\Àíäðåé\\Documents\\_Àñïèðàíòóðà\\tmp\\2022\\Matr_1.txt"); for (k=0; k<ksu; k++) zapisvfile(ms4[k], ksu, "C:\\Users\\Àíäðåé\\Documents\\_Àñïèðàíòóðà\\tmp\\2022\\Matr_4.txt");
	r = 0.0; fa=r; fb=r; for (j = 0; j < ksu; j++) { t = tet[j]; if (r < t) r = t; if (t>ep) { fa=fa+t; fb=fb+ht; } } j=5; mvyz[j] = r; 
	if (fabs(fb)>eps) fa=fa/fb; else fa=0.0;
	cout << "\tSred Temp NR = " << fa; //FILE *fo = fopen("C:\\Users\\Àíäðåé\\Documents\\_Àñïèðàíòóðà\\tmp\\2022\\Temp_NR.txt", "at"); fprintf(fo, "%0.15lf\n", fa); fclose(fo);
	for (k = 0; k < ksu; k++) tet[k] = te[k];
	q = 0; while ((q<qk) && (ra>e)) {
		tc = (ta + tb) / 2e0;
		tet = opredTempStenShaFragm(tet, ksu, ktpvo, vte, ete, ktptk, chis, dmv, htch, hvozd, qc, ta, ht);
		fa = vychNevyaz(ms1, ms4, tet, ssc, ksu); tmaa = 0.0; for (k = 0; k < ksu; k++) if (tmaa < tet[k]) tmaa = tet[k];
		tet = opredTempStenShaFragm(tet, ksu, ktpvo, vte, ete, ktptk, chis, dmv, htch, hvozd, qc, tb, -ht);
		fb = vychNevyaz(ms1, ms4, tet, ssc, ksu); tmab = 0.0; for (k = 0; k < ksu; k++) if (tmab<tet[k]) tmab = tet[k];
		tet = opredTempStenShaFragm(tet, ksu, ktpvo, vte, ete, ktptk, chis, dmv, htch, hvozd, qc, tc, ht);
		fc = vychNevyaz(ms1, ms4, tet, ssc, ksu);
		if ((fc*fb>0.0) && (fa*fc<0.0)) tb = tc; if ((fc*fa>0.0) && (fb*fc < 0.0)) ta = tc;
		ra = fabs(tmab - tmaa);
		q++;
	}
	tet = opredTempStenShaFragm(tet, ksu, ktpvo, vte, ete, ktptk, chis, dmv, htch, hvozd, qc, tc, 1.0);
	t = 0.0; for (k = 0; k < ksu; k++) for (j = 0; j<ksu; j++) { tc = tet[k] - tet[j]; if (tc>t) t = fabs(tc); } //ìàêñèìàëüíàÿ ðàçíîñòü òåìïåðàòóð
	j=0; mvyz[j] = t;
	j=4; mvyz[j] = t / (htch*ksuf + hvozd*(ksuf - 1e0));
	j=1; mvyz[j] = qc; //ïëîòíîñòü òåïëîâîãî ïîòîêà
	t = 0.0; for (k = 0; k < ksu; k++) t = t + tet[k]; t = t / ksuf; //ñðåäíÿÿ òåìïåðàòóðà êîíå÷íàÿ //cout << "T_sred_tet = " << t << "\tT_sred = " << tc << "\ttmin = " << tmaa << "\ttmax = " << tmab << "\tra_tem = " << ra << endl;
	j=2; mvyz[j] = t;
	t = 0.0; for (k = 0; k < ksu; k++) t = t + te[k]; t = t / ksuf; //ñðåäíÿÿ òåìïåðàòóðà íà÷àëüíàÿ
	j=3; mvyz[j] = t;
	f = koelvyma - ksu; for (j = f; j < koelvyma; j++) mvyz[j] = tet[j - f]; //ðàñïðåäåëåíèå òåìïåðàòóð
	delete[]tet;
	return mvyz;
}
void vyvodfile(double *ao, int sao, int zf, double hvv, char *nafa)
{
	int k; FILE *fo = fopen(nafa, "at");
	if (!fo) { cout << sfnos << endl; k = getchar(); exit(1); }
	if (zf < 1) {
		fprintf(fo, "\nhv = %0.10lf\n", hvv); 
	} for (k = 0; k < sao; k++) fprintf(fo, "%0.15lf\n", ao[k]); fprintf(fo, "\n"); fclose(fo);
}
double opredKTPTKTochSha(double *ktptks, double *te, double temp, int ce)
{
	int n = ce, f = 1, p = 0, k; 
	double e=1e-4, ktp = 0.0, ko = 0.0, x1=0.0, x2=0.0, y1=0.0, y2=0.0, b=0.0, dt=0.0; 
	if ((temp>=te[0]) && (temp<=te[n-1])) {
	for (k = 0; k<n; k++)
		if ((te[k] >= temp) && (f>0)) { p = k; f = 0; break; } 
	if (!p) { if (!f) p = 1; else { p = n - 1; f = 0; }	} }
	else if (temp<te[0]) { p=1; f=0; }
	else if (temp>te[n-1]) { p=n-1; f=0; }
	if ((!f) && (p>0)) {
		x2=te[p];
		x1=te[p - 1];
		dt = x2 - x1;
		if (fabs(dt) > e) {
			y2=ktptks[p];
			y1=ktptks[p - 1];
			b=y1;
			if ((n-1)==p) b=y2;
			ko = (y2 - y1) / dt;
			ktp = b + ko*(temp - x1);
		}
	}
	return ktp;
}
double **opredTempLPStenSha(double *Ts, double *Tss, double *Tsr, double *Tna, double Tnach, int n, double *ktpvo, double *vte, double *ete, double *ktptk, int ce, int dmv, double htk, double hnf, double ptpob, int kost, char *snm)
{
	int q = 4, m, k; double lam, tt, lamvo, lamt, ht, **mu = new double*[q];;
	Ts = new double[kost]; Tss = new double[kost]; Tsr = new double[kost]; Tna = new double[n];
	if ((!Tna) || (!Ts) || (!Tss) || (!mu)) { cout << snm << endl; k = getchar(); exit(1); }
	for (k = 0; k < kost; k++) { Ts[k] = 0.0; Tss[k] = 0.0; Tsr[k] = 0.0; } for (k = 0; k < n; k++) Tna[k] = 0.0;
	Tna[0] = Tnach; Ts[0] = Tnach; q = 1; m = 0;
	for (k = 1; k < n; k++)  {
		tt = Tna[k - 1]; lamt = opredKTPTKTochSha(ktptk, ete, tt, ce); if (lamt < 0.0) lamt = 0.0; //èùåì ÊÒÏ òâåðäîãî ñêåëåòà ïðè äàííîé òåìïåðàòóðå
		lamvo = opredKTPTKTochSha(ktpvo, vte, tt, dmv); if (lamvo<0.0) lamvo = 0.0; //èùåì ÊÒÏ âîçäóõà ïðè äàííîé òåìïåðàòóðå
		if (k % 2) { ht = htk; lam = lamt; }
		else { ht = hnf; lam = lamvo; }
		if (fabs(lam)>0.0) Tna[k] = tt - ptpob*ht / lam; else Tna[k] = Tna[k - 1]; //ðàññ÷èòûâàåì òåìïåðàòóðó íà ãðàíèöàõ ñòåíîê 
		if ((k % 2)) { Tss[m] = Tna[k]; m++; }
		else { Ts[q] = Tna[k]; q++; }
	}
	for (k = 0; k < kost; k++) Tsr[k] = (Ts[k] + Tss[k]) / 2e0; //ðàññ÷èòûâàåì òåìïåðàòóðó âíóòðè ñòåíîê 
	k = 0; mu[k] = Ts; k++; mu[k] = Tss; k++; mu[k] = Tsr; k++; mu[k] = Tna; return mu;
}
double **RaschVneshIzluchSha(double *Tra, double *Ref, double *prot, double *hlr1, double *hrl1, int kost, double hlr0, double hrl0, char *snm)
{
	int k = 3, j, m, q = 2; double *khrl = new double[kost], *khlr = new double[kost], *ri = new double[q], **mu = new double*[k];
	hrl1 = new double[kost]; hlr1 = new double[kost];
	if ((!khrl) || (!khlr) || (!ri) || (!hrl1) || (!hlr1) || (!mu)) { cout << snm << endl; k = getchar(); exit(1); }
	for (k = 0; k < kost; k++) { khrl[k] = 0.0; khlr[k] = 0.0; hrl1[k] = 0.0; hlr1[k] = 0.0; } for (k = 0; k < q; k++) ri[k] = 0.0;
	double w0, w1, w2, w3, wk, slr, srl, tta, ttb, tt;
	khlr[0] = 1e0; j = kost - 1; khrl[j] = 1e0;
	for (k = 1; k < kost; k++) {
		khlr[k] = khlr[k - 1] * Tra[k - 1];
		khrl[j - 1] = khrl[j] * Tra[j];
		j--;
	} //for (k=0; k<kost; k++) cout << "khrl " << k << " = " << khrl[k] << "\tkhlr " << k << " = " << khlr[k] << endl;
	q = 0; slr = 0.0; srl = 0.0; for (j = 0; j < kost; j++) //óçíàåì, êàêàÿ äîëÿ âíåøíåãî èçëó÷åíèÿ äîøëà äî j-îé ñòåíêè - ó÷èòûâàåì âêëàä îò âñåõ ñòåíîê
	{
		hlr1[j] = 0.0; hrl1[j] = 0.0; //âíåøíåå èçëó÷åíèå ïàäàåò ñ îáåèõ ñòîðîí
		tta = 0.0; ttb = 0.0; m = q;
		for (k = 0; k<kost; k++) {
			w0 = prot[q]; w1 = prot[q + 1]; w2 = prot[q + 2]; w3 = prot[q + 3]; wk = w2 + w3; //äëÿ âíåøíåãî èçëó÷åíèÿ, ðàñïðîñòðàíÿþùåãîñÿ ñëåâà íàïðàâî
			tt = Ref[k] * w2 + Tra[k] * w3; //äîëÿ ýíåðãèè, îòðàæåííàÿ îò k-îé ñòåíêè, è ïðîøåäøàÿ ÷åðåç íåå, ïðèøëà ñïðàâà ê j-îé ñòåíêå
			if (fabs(wk)>0.0) {
				tta = tta + tt*khlr[k] * w0 / wk; //äîëÿ ýíåðãèè, îòðàæåííàÿ îò k-îé ñòåíêè, è ïðîøåäøàÿ ÷åðåç íåå, ïðèøëà ñëåâà ê j-îé ñòåíêå
				ttb = ttb + tt*khlr[k] * w1 / wk;
			} //äëÿ ó÷åòà ïðè ïîäñ÷åòå ëó÷èñòîé ýíåðãèè, ðàñïðîñòðàíÿþùåéñÿ ñïðàâà íàëåâî
			q = q + 4;
		} q = m + 4 * kost - 1; m = q; //ñ÷èòàåì, ÷òî ñòåíêè, äî êîòîðûõ äîøëî èçëó÷åíèå, êàê áû "ñàìè" èçëó÷àþò, èç-çà òîãî, ÷òî íà íèõ ïîïàëî âíåøíåå èçëó÷åíèå
		for (k = (kost - 1); k >= 0; k--) {
			w0 = prot[q - 3]; w1 = prot[q - 2]; w2 = prot[q - 1]; w3 = prot[q]; wk = w2 + w3; q = q - 4; //äëÿ âíåøíåãî èçëó÷åíèÿ, ðàñïðîñòðàíÿþùåãîñÿ ñïðàâà íàëåâî
			tt = Ref[k] * w3 + Tra[k] * w2; //äåëåíèå íà äâà ïîòîêà
			if (fabs(wk) > 0.0) {
				tta = tta + tt*khrl[k] * w0 / wk; //äëÿ ó÷åòà ëó÷èñòîé ýíåðãèè, ðàñïðîñòðàíÿþùåéñÿ ñëåâà íàïðàâî, ïàäàåò ñëåâà îò j-îé ñòåíêè
				ttb = ttb + tt*khrl[k] * w1 / wk;
			} //òî, ÷òî ïîïàäàåò ñïðàâà íàëåâî íà ñòåíêó, ñïðàâà îò j-îé ñòåíêè
		} q = m + 1;
		hlr1[j] = tta*hlr0; //óçíàåì âåëè÷èíó â àáñîëþòíûõ åäèíèöàõ ýòîé ëó÷èñòîé ýíåðãèè - ñëåâà îò ïëàñòèíêè, ïàäàåò ñëåâà íàïðàâî
		hrl1[j] = ttb*hrl0; //ñïðàâà îò ïëàñòèíêè, ïàäàåò ñïðàâà íàëåâî
	} slr = slr + Tra[kost - 1] * hlr1[kost - 1] + hrl0*Ref[kost - 1]; ri[0] = slr; //òî, ÷òî âûøëî èç ïîñëåäíåé ñòåíêè âïðàâî
	srl = srl + Tra[0] * hrl1[0] + Ref[0] * hlr1[0]; ri[1] = srl; //òî, ÷òî âûøëî èç ïåðâîé ñòåíêè âëåâî
	hlr1[0] = hlr0; hrl1[kost - 1] = hrl0; //for (k=0; k<ks; k++) cout << "hrl " << k << " = " << hrl1[k] << "\thlr " << k << " = " << hlr1[k] << endl;
	delete[]khlr; delete[]khrl; //cout << "Ras Vn Iz Sha k" << endl;
	k = 0; mu[k] = hlr1; k++; mu[k] = hrl1; k++; mu[k] = ri; return mu;
}
double **RaschSobLuchPlotTepPot(int kost, double *prot, double *Ts, double *Tss, double *Tra, double *Ref, double *Ab, double slr, double srl, double *ao, int sao, char *snm)
{
	int j, q = 3, k, p = sao;
	double tta, ttb, ttc, tt, w0, w1, w2, w3, wk, sig = 5.67e-8, **mu = new double*[q];
	double *sislr = new double[kost], *sisrl = new double[kost];
	if ((!sisrl) || (!sislr) || (!mu)) { cout << snm << endl; k = getchar(); exit(1); }
	q = 0; for (j = 0; j < kost; j++) { //óçíàåì, êàêàÿ ýíåðãèÿ ñîáñòâåííîãî èçëó÷åíèÿ äîøëà äî j-îé ñòåíêè
		sislr[j] = 0.0; sisrl[j] = 0.0; tta = 0.0; ttb = 0.0;
		for (k = 0; k<kost; k++) {
			w0 = prot[q]; w1 = prot[q + 1]; w2 = prot[q + 2]; w3 = prot[q + 3]; wk = w2 + w3;
			tt = pow(Ts[k], 4e0)*w2 + pow(Tss[k], 4e0)*w3;
			if (fabs(wk)>0.0) {
				ttc = Ab[k] * w0*tt / wk; tta = tta + ttc; // òî, ÷òî ïîïàäàåò ñëåâà íàïðàâî
				tt = Ab[k] * w1*tt / wk; ttb = ttb + tt;
			} // òî, ÷òî ïîïàäàåò ñïðàâà íàëåâî
			q = q + 4;
		}
		sislr[j] = sig*tta; //ñîáñòâåííîå èçëó÷åíèå ñòåíîê ñëåâà íàïðàâî è ñïðàâà íàëåâî
		sisrl[j] = sig*ttb;
	}
	slr = slr + Tra[kost - 1] * sislr[kost - 1];
	slr = slr + Ab[kost - 1] * sig*pow(Tss[kost - 1], 4e0);
	srl = srl + Tra[0] * sisrl[0];
	srl = srl + Ab[0] * sig*pow(Ts[0], 4e0);
	sislr[0] = 0.0; sisrl[kost - 1] = 0.0; //ñòåíîê âíå ìíîãîñëîéíîé ñòåíêè íåò, èçëó÷åíèå íèîòêóäà íå ïàäàåò, åñòü òîëüêî âíåøíåå èçëó÷åíèå //ra=slr-srl; if (!vyb) cout << "slr = " << slr << "\tsrl = " << srl << "\tra = " << ra << "\tqc = " << qobsha << endl; //èçëó÷åíèå çà êðàéíåé ïðàâîé ñòåíêîé è çà êðàéíåé ëåâîé
	ao[p] = slr; p++; ao[p] = srl;
	k = 0; mu[k] = ao; k++; mu[k] = sislr; k++; mu[k] = sisrl; return mu;
}
double **RasLuchPloTepPot(int kost, double *hrl1, double *hlr1, double *ao, double *Tra, double *Ref, double *Ab, int sao, double *sislr, double *sisrl, double *Tsr, char *snm)
{
	int j, k = 3, saot = sao;
	double *Erlr = new double[kost], *Elrr = new double[kost], *Erl = new double[kost], *Elr = new double[kost], *Etem = new double[kost];
	double *Eres = new double[kost], *Eresl = new double[kost], *Eresr = new double[kost], **mu = new double*[k];
	double srl, slr, tth, tat, ttb, tta;
	if ((!Erlr) || (!Elrr) || (!Erl) || (!Elr) || (!Eresr) || (!Eresl) || (!Eres) || (!Etem)) { cout << snm << endl; k = getchar(); exit(1); }
	for (j = 0; j < kost; j++) { Erlr[j] = 0.0; Elrr[j] = 0.0; Erl[j] = 0.0; Elr[j] = 0.0; Eres[j] = 0.0; Eresl[j] = 0.0; Eresr[j] = 0.0; }
	srl = 0.0; srl = 0.0; tth = 0.0; tat = 0.0;
	for (k = 1; k < kost; k++) {
		srl = hrl1[k] * Tra[k]; //ñëåâà îò k-îé ñòåíêè
		slr = hlr1[k]; tta = slr + srl*Ref[k - 1]; Elr[k] = Elr[k] + tta; //â âîçäóøíîì ïðîìåæóòêå ìåæäó (k-1)-îé è k-îé ñòåíêàìè - èçëó÷åíèå, èäóùåå ñëåâà íàïðàâî
		ttb = srl + slr*Ref[k]; Erl[k] = Erl[k] + ttb; //èçëó÷åíèå, èäóùåå ñïðàâà íàëåâî
		Eresl[k] = Eresl[k] + tta - ttb; //âïðàâî - âëåâî
		slr = sislr[k]; srl = sisrl[k] * Tra[k]; tta = slr + srl*Ref[k - 1]; //ñëåâà - íàïðàâî
		Elr[k] = Elr[k] + tta; ttb = srl + slr*Ref[k]; //ñïðàâà - íàëåâî
		Erl[k] = Erl[k] + ttb; Eresl[k] = Eresl[k] + tta - ttb; //ðåçóëüòèðóþùåå èçëó÷åíèå ñëåâà îò k-îé ñòåíêè
	} for (k = 0; k < (kost - 1); k++) {
		slr = hlr1[k] * Tra[k]; // ñïðàâà îò k-îé ñòåíêè
		srl = hrl1[k + 1]; tta = srl + slr*Ref[k + 1]; //âëåâî
		Erlr[k] = Erlr[k] + tta; //ñïðàâà îò ñòåíêè, èçëó÷åíèå èäåò ñïðàâà íàëåâî
		ttb = srl*Ref[k] + slr; Elrr[k] = Elrr[k] + ttb; //âïðàâî
		Eresr[k] = Eresr[k] + ttb - tta; //ðåçóëüòèðóþùåå èçëó÷åíèå ñïðàâà îò k-îé ñòåíêè
		slr = sislr[k] * Tra[k]; srl = sisrl[k + 1]; tta = slr + srl*Ref[k]; //âïðàâî
		Elrr[k] = Elrr[k] + tta; ttb = srl + slr*Ref[k + 1]; //âëåâî
		Erlr[k] = Erlr[k] + ttb; Eresr[k] = Eresr[k] + tta - ttb;
	}
	for (k = 0; k < ks; k++) Eres[k] = Eresl[k] - Eresr[k];
	ao = usrednen(ao, Tsr, saot, kost); saot++; //2
	ao = usrednen(ao, Eresl, saot, kost - 1); saot++; //3
	ao = usrednen(ao, Eresr, saot, kost - 1); saot++; //4
	ao = usrednen(ao, Eres, saot, kost - 1); saot++; //5
	ao = usrednen(ao, Erl, saot, kost - 1); saot++; //6
	ao = usrednen(ao, Elr, saot, kost - 1); ao[saot] = ao[saot] - ao[saot - 1]; saot++; //7
	ao = usrednen(ao, Elrr, saot, kost - 1); saot++; //8
	ao = usrednen(ao, Erlr, saot, kost - 1); ao[saot] = ao[saot - 1] - ao[saot]; saot++; //9
	ao[saot] = (ao[saot - 1] + ao[saot - 3]) / 2.0; //10 //vyvodfile(ao,saot,zf,hvsha,sfo);
	for (k=0; k<kost; k++) { if (!k) tta=Eresl[k]; else if (!(k+1-kost)) tta=Eresr[k]; else tta=(Eresr[k-1]+Eresl[k])/2e0; Etem[k]=tta; } 
	delete[]Eresl; delete[]Eresr; delete[]Erl; delete[]Elr; delete[]Elrr; delete[]Erlr;
	k = 0; mu[k] = ao; k++; mu[k] = Eres; k++; mu[k]=Etem; return mu;
}
double *opredTempStenShaFragm(double *Tna, int n, double *ktpvo, double *vte, double *ete, double *ktptk, int ce, int dmv, double htk, double hnf, double ptpob, double tenac, double zn)
{
	int k; double lamt, lamvo, lam, ht, tt; Tna[0] = tenac;
	for (k = 1; k < n; k++)  {
		tt = Tna[k - 1];
		lamt = opredKTPTKTochSha(ktptk, ete, tt, ce); //èùåì ÊÒÏ òâåðäîãî ñêåëåòà ïðè äàííîé òåìïåðàòóðå
		lamvo = opredKTPTKTochSha(ktpvo, vte, tt, dmv); //èùåì ÊÒÏ âîçäóõà ïðè äàííîé òåìïåðàòóðå
		if (k % 2) { ht = htk; lam = lamt; }
		else { ht = hnf; lam = lamvo; }
		Tna[k] = tt + zn*ptpob*ht / lam;  //ðàññ÷èòûâàåì òåìïåðàòóðó íà ãðàíèöàõ ñòåíîê 
	} return Tna;
}
double **RaschRTASha(int kost, double htm, double kta, double ktb, double hvp, double tc, int v, int c, int w, int u)
{
	double *te=NULL, e = tocrassha, **mauk=NULL; int k = kost, j, r;
	if (!v) {
		alphaSha = kopoSha(kta, ktb, 2, k, htm, hvp, tc, 0, alphaSha);
		te = kopoSha(kta, ktb, 0, k, htm, hvp, tc, 0, alphaSha);
		if (!c) {
			k = kost;
			if (Rash) delete[]Rash; Rash = new double[k];
			if (Rtsh) delete[]Rtsh; Rtsh = new double[k];
			if (Rsh) delete[]Rsh; Rsh = new double[k];
			if ((!Rash) || (!Rtsh) || (!Rsh)) { cout << snms << endl; j = getchar(); exit(1); }
			k = kost; Rash = opredKoefOtr(te, Rash, k, tocrassha, 0, cem, mko, etesha, 0);
			for (j = 0; j < k; j++) { Rtsh[j] = Rash[j]; Rsh[j] = Rash[j]; }
			if (Tash) delete[]Tash; Tash = new double[k];
			if (Ttsh) delete[]Ttsh; Ttsh = new double[k];
			if (Tsh) delete[]Tsh; Tsh = new double[k];
			if ((!Tash) || (!Ttsh) || (!Tsh)) { cout << snms << endl; j = getchar(); exit(1); }
			if (Atsh) delete[]Atsh; Atsh = new double[k];
			if (Aash) delete[]Aash; Aash = new double[k];
			if (Ash) delete[]Ash; Ash = new double[k];
			if ((!Aash) || (!Atsh) || (!Ash)) { cout << snms << endl; j = getchar(); exit(1); }
			for (j = 0; j < k; j++) {
				Tash[j] = alphaSha[j] * htm; Tash[j] = exp(-Tash[j]); Aash[j] = 1e0 - Tash[j] - Rash[j];
				if (Aash[j] < 0.0) { Aash[j] = alphaSha[j] * htm; Tash[j] = 1e0 - Rash[j] - Aash[j]; }
				Ttsh[j] = Tash[j]; Atsh[j] = Aash[j]; Ash[j] = Aash[j]; Tsh[j] = Tash[j];
			}
			k = kost; mauk = izmRTASha(te, k, Rash, Tash, Aash, Rsh, Tsh, Ash, 0, 1);
			r = 6; mauk[r] = Rtsh; r++; mauk[r] = Ttsh; r++; mauk[r] = Atsh;
		}
		else if (c == 1) { r = 1; mauk = new double*[r]; if (!mauk) { cout << snms << endl; k = getchar(); exit(1); } mauk[0] = te; }
	}
	else if (v == 1) {
		r = 1; mauk = new double*[r]; if (!mauk) { cout << snms << endl; k = getchar(); exit(1); }
		te = kopoSha(0.0, 0.0, 1, kost, htm, hvp, tc, 0, alphaSha); mauk[0] = te;
	}
	if (!u) mauk[0] = te; return mauk;
}
double *oprRasTemNach(int ce, int cee, double *teks, double *koe, int kost, double *xi, double htch, double hvozd, double hkosha, double a, double b, int w)
{
	double e = tocrassha, hkx = 0.0, ht = 0.0, tsre; int k, j;
	if (!w) {
		k = 1; for (j = 0; j < ce; j++) if ((Tg[j] < e) || (Th[j] < e) || (qob[j] < e)) { k = 0; break; }
		if (!k) opredtemphc(ektpsha, etesha, ce, cee, y0sha);
		hkx = hkosha; koe[0] = (Th[vtsh] - Tg[vtsh]) / y0sha; koe[1] = Tg[vtsh]; tmasha = Tg[vtsh]; tmisha = Th[vtsh];
	}
	else if (w == 1) { hkx = y0sha / 2e0; koe[0] = a; koe[1] = b; tmasha = b; tmisha = b - a*y0sha; }
	xi[0] = hkx + htch / 2e0; ht = hvozd + htch; for (k = 1; k < kost; k++) xi[k] = xi[k - 1] + ht; //ìàññèâ ñåðåäèí êàæäîé èç ñòåíîê ïî òîëùèíå
	for (k = 0; k < kost; k++) teks[k] = koe[0] * xi[k] + koe[1];
	tsre = (teks[0] + teks[kost - 1]) / 2e0; qobsha = opredKTPTKTochSha(qob, etesha, tsre, ce); //for (k=0; k<kost; k++) cout << "k = " << k << "\txk = " << xi[k] << "\ttex = " << teks[k] << endl;
	return teks;
}
double *oprEffDoliTepPeren(double ko, double d, double por)
{
	int k, j, f, kost = ks, ksu = 2 * ks; double hvozd, htch, hf = 1e0, e = tocrassha;
	double *tepo = new double[ksu], *dol = new double[cem], r, p, sa, sb, sc, t, fa, fb, fc;
	if ((!tepo) || (!dol)) { cout << snms << endl; k = getchar(); exit(1); }
	for (j = 0; j < ksu; j++) tepo[j] = 0.0;
	hvozd = ko; htch = hvozd*(hf - por) / por;
	k = 1; for (j = 0; j < cem; j++) if (qob[j] < tocrassha) k = 0;
	if (!k) opredtemphc(ektpsha, etesha, cem, ceektp - 1, y0sha); //cout << "hvoz = " << hvozd << "\tht = " << htch << endl;
	for (j = 0; j < cem; j++) { //îïðåäåëÿåì ÝÊÒÏ ìíîãîñëîéíîé ñòåíêè
		tepo = opredTempStenShaFragm(tepo, ksu, ktpvosha, vtesha, etesha, kttk, cem, dmkv, htch, hvozd, qob[j], etesha[j], -hf); //â ñåðåäèíå ñëîÿ
		r = 0.0; for (k = 0; k < ksu; k++) for (f = 0; f<ksu; f++) { p = tepo[k] - tepo[f]; if (p>r) r = p; }
		p = hvozd*(d - hf) + htch*d; r = r / p; t = qob[j] / r; ecktpsha[j] = t;
	} //for (j=0; j<cem; j++) cout << "SKTPTK ( " << j << " ) = " << ecktpsha[j] << endl;
	delete[]tepo;
	f = 1000; for (j = 0; j<cem; j++)
	{
		sa = 0.0; sb = 1e0; k = 0;
		do {
			sc = (sa + sb) / 2e0;
			fa = kttk[j] * sa + ecktpsha[j] * (hf - sa) - ektpsha[j]; //ýôôåêòèâíûå ÊÒÏ ìíîãîñëîéíîé ñòåíêè è ïåðåìû÷êè äîëæíû ñðàâíÿòüñÿ
			fb = kttk[j] * sb + ecktpsha[j] * (hf - sb) - ektpsha[j]; //÷òîáû íàéòè îòíîñèòåëüíûå äîëè ïëîùàäåé ñå÷åíèÿ ïåðåíîñà îáùåé ÏÒÏ
			fc = kttk[j] * sc + ecktpsha[j] * (hf - sc) - ektpsha[j];
			if ((fc*fb>0.0) && (fa*fc<0.0)) sb = sc;
			if ((fc*fa>0.0) && (fb*fc<0.0)) sa = sc;
			r = fabs(sa - sb); k++;
		} while ((r>tocrassha) && (k<f));
		dol[j] = sc;
	}
	return dol;
}
double *KorrZnachVozdPros(double hps, double ksf, double por, int vy)
{
	int j = 0, k = 1000, q=0; double pa = 1e-2, pb = 1e0, *po, pc, ra = fabs(pa - pb), *pkc=new double[1];
	double fa, fb, fc, ta, tb, tc, tca, tcb, tcc, ka = hps*pa / por, kb = pb*hps / por, kc; //cout << "hps = " << hps << "\tksuf = " << ksf << "\tpor = " << por << endl;
	dpctsm=new double[cem]; if (!dpctsm) { cout << snms << endl; q=getchar(); exit(1); }
	for (q=0; q<cem; q++) { j=0; pa = 1e-2; pb = 1e0; ra = fabs(pa - pb); ka = hps*pa / por; kb = pb*hps / por;
	while ((ra>tocrassha) && (j < k)) { //ïîäòÿãèâàåì ïîðèñòîñòü ê çíà÷åíèþ, êîòîðîå çàäàëè èçíà÷àëüíî, âî âðåìÿ ïîäñòðîéêè ÝÊÒÏ
		pc = (pa + pb) / 2e0; kc = hps*pc / por;
		po = oprEffDoliTepPeren(kc, ksf, pc); tc = po[q]; delete[]po; //ïðè 373 Ê
		tcc = kc*(1e0 - pc) / pc; fc = (1e0 - tc)*kc / (kc + tcc) - por;
		ka = hps*pa / por;
		po = oprEffDoliTepPeren(ka, ksf, pa); ta = po[q]; delete[]po; //îïðåäåëÿåì äîëþ ïëîùàäè ñå÷åíèÿ ïåðåìû÷êè
		tca = ka*(1e0 - pa) / pa; fa = (1e0 - ta)*ka / (ka + tca) - por;
		kb = hps*pb / por;
		po = oprEffDoliTepPeren(kb, ksf, pb); tb = po[q]; delete[]po; //÷åðåç ïåðåìû÷êó òåïëî ðàñïðîñòðàíÿåòñÿ ÷èñòîé òåïëîïðîâîäíîñòüþ
		tcb = kb*(1e0 - pb) / pb; fb = (1e0 - tb)*kb / (kb + tcb) - por;
		if ((fc*fb > 0.0) && (fa*fc<0.0)) pb = pc; if ((fc*fa>0.0) && (fb*fc < 0.0)) pa = pc;
		j++; ra = fabs(pa - pb); } 
	dpctsm[q]=tc; cout << "Dol Plo CTP = " << tc << endl; }
	for (j=0; j<cem; j++) cout << "EC KTP TK ( " << j << " ) = " << ecktpsha[j] << endl;
	if (!vy) { pkc[0]=kc; return pkc; } //ñêîððåêòèðîâàííîå çíà÷åíèå òîëùèíû âîçäóøíîé ïðîñëîéêè (ðàçìåð ïîðû), êîãäà ââåëè ïåðåìû÷êó
	else if (vy == 1) return dpctsm;
} //äîëÿ ïëîùàäè, ÷åðåç êîòîðóþ ïðîèñõîäèò ïåðåíîñ òåïëà ÷èñòîé òåïëîïðîâîäíîñòüþ
double *opredPolTempTvKarShaFragm(double *Tna, int n, double *ete, double *ktptk, int ce, double htk, double hvp, double ptpob, double tenac, double zn)
{
	int k; double lamt, hh = hvp + htk, ht = htk + hvp / 2e0, tt; Tna[0] = tenac;
	for (k = 1; k < n; k++)  {
		tt = Tna[k - 1];
		lamt = opredKTPTKTochSha(ktptk, ete, tt, ce); //èùåì ÊÒÏ òâåðäîãî ñêåëåòà ïðè äàííîé òåìïåðàòóðå
		Tna[k] = tt + zn*ptpob*ht / lamt;  ht = ht + hh;
	} return Tna;
}  //ðàññ÷èòûâàåì òåìïåðàòóðó íà ãðàíèöàõ ñòåíîê
double RaschAlphaTvKarSha()
{
	int l = 2, k=0, d = 10, q=0, cfk = l, cei=0;
	long j=0, jk = 100 * 100 * 100, pj=0, h=0;
	double x = 0.0, y = 0.0, p = 0.0, xt = 0.0, yp = 0.0, hf = 1e0, tc = 22.0 + te0;
	double altc, *srra=NULL, pors=1e-6, lamtem=1448.0, dvpn = lamtem*pors / tc / 4e0;
	double *pn = new double[d], *alx = new double[d], *rcf = new double[cfk];
	double *rapo, srp, marp, ce, cet, *pp=NULL, *legr=NULL, **pt=NULL, *prgr=NULL;
	pt=vybFunRasPorpoRazSha(porsha, vrsh, vystsha);
	k=0; rapo=pt[k]; k++; srra=pt[k]; k++; prgr=pt[k]; k++;
	legr=pt[k]; k++; pp=pt[k]; j=0; srp=pp[j]; if (pp) delete[]pp; k++;
	pp=pt[k]; marp=pp[j]; if (pp) delete[]pp; if (pt) delete[]pt;
	cet = ce; j = 0; while (cet > 0.0) { cet = cet - hf; j++; } cei = j; //cout << "cem_srp = " << cei << "\tsrp = " << srp << "\t"; cout << endl; for (j=0; j<cei; j++) if (j<10) cout << "j = " << j << "\trpr = " << rapo[j] << "\tlegr = " << legr[j] << "\t"; cout << endl;
	x = 0.0; for (j = 0; j < cei; j++) if (j <= 31) x = x + srra[j] * rapo[j]; pors = x*porsha / srp;
	double pr = 0.0, rmf = 0.0, prf = 0.0, po = 0.0, *alsf = new double[cfk];
	for (j = 0; j < RAND_MAX; j++) rmf = rmf + hf; for (j = 0; j < jk; j++) po = po + hf;
	if ((pn) && (alx) && (rcf) && (alsf)) { for (j = 0; j < d; j++) { pn[j] = 0.0; alx[j] = 0.0; } 
	for (j = 0; j < cfk; j++) { rcf[j] = 0.0; alsf[j] = 0.0; } }
	else { cout << snms << endl; j = getchar(); exit(1); }
	long lt; unsigned int st; lt = time(NULL); st = (unsigned int)(lt - (lt % 2)) / 2; srand(st);
	for (k = 0; k < l; k++) {
		x = RasFracXeffSha60(k); //ðàçìåð ÷àñòèöû
		rcf[k] = x*1e-6; y = x*pors; //ðàçìåð ïîðû
		for (j = 0; j < d; j++) pn[j] = 0.0;
		for (j = 0; j < jk; j++) {
			pj = rand(); prf = 0.0; for (h = 0; h < pj; h++) prf = prf + hf; pr = prf / rmf;
			yp = y*pr; xt = yp*(hf - pors) / pors;
			p = x / (xt + yp);
			pr = 0.0; for (h = 0; h < d; h++)	{ xt = pr + hf; if ((p >= pr) && (p < xt)) pn[h] = pn[h] + hf; pr = xt; }
		}
		pr = 0.0; for (j = 0; j < d; j++) { pn[j] = pn[j] / po; pr = pr + pn[j]; } //cout << "Summa = " << pr << endl; for (j=0; j<d; j++) cout << "pn ( " << j << " ) = " << pn[j] << "\t";
		for (j = 0; j < d; j++) pn[j] = pn[j] / pr;
		for (j = 2; j < d; j++) {
			p = 0.0; for (h = 0; h<j; h++) p = p + hf;
			yp = pors*x*1e-6 / (p - hf); xt = (hf - pors)*x*1e-6 / p; //cout << "x = " << x << "\txp = " << yp << "\txt = " << xt << "\t";
			if (yp>dvpn) {
				lamtem = F0_lamT(yp*tc); if (lamtem<0.0) lamtem = 0.0; if (lamtem>hf) lamtem = hf;
				alx[j] = BolTochRasAlpha(0, j, yp, xt, tc, ktpvosha, vtesha, etesha, cem, dmkv, snms, Tsh, Rsh, 2 * N, kttk, Ash, 1, Rash, Tash, Aash, Rtsh, Ttsh, Atsh)*lamtem;
			}
			else alx[j] = 0.0;
		}
		pt = RaschRTASha(d, xt, 0.0, 0.0, yp, tc, 1, 0, 0, 0); pp = pt[0]; altc = pp[0]; delete[]pp; delete[]pt;
		alx[0] = 0.0; alx[1] = altc / (hf - pors); //for (j=0; j<d; j++) cout << "j = " << j << "\talx = " << alx[j] << "\t";
		for (j = 1; j<d; j++) {
			p = 0.0; for (h = 0; h <= j; h++) p = p + hf;
			yp = pors*x*1e-6 / (p - hf); if (j>1) xt = oprProcSoderpoPoris(rapo, legr, yp, cei); else xt = 1e0; //cout << "j = " << j << "\txt = " << xt << "\t";
			alsf[k] = alsf[k] + pn[j] * alx[j] * xt;
		}
	}
	x = 0.0; yp = 0.0; for (j = 0; j < cfk; j++) { x = x + alsf[j]; yp = yp + hf; } x = x / yp; //for (j=0; j<cfk; j++) cout << "j = " << j << "\tal_sr = " << alsf[j] << endl; 
	delete[]rapo; delete[]srra; delete[]rcf; delete[]pn; delete[]alx; 
	delete[]alsf; delete[]legr; delete[]prgr;
	x = (x / altc); printf("dkops = %0.10lf\n", x); //îñëàáëåíèå ÊÏ çà ñ÷åò ïîðèñòîé ñòðóêòóðû âåðìèêóëèòà
	return x;
}
double RasFracXeffSha60(int v)
{
	int l = 2, k; double *mkbr = new double[l], *mv = new double[l], *tol = new double[l];
	k = 0; mkbr[k] = 238.57; k++; mkbr[k] = 227.973; k++;
	k = 0; mv[k] = 1.706; k++; mv[k] = 1.1; k++;
	k = 0; tol[k] = 0.7; k++; tol[k] = 0.68; k++;
	double rokbr = 2.75, rov = 2.69, *xv = EffectTols(mkbr, mv, tol, rov, rokbr, l), xsr = 0.0;
	if (!v) xsr = xv[0]; else if (v == 1) xsr = xv[1];
	delete[]mkbr; delete[]mv; delete[]tol; delete[]xv; return xsr;
}
double RasIzlSerStenNac(double *Refl, double *Tran, double *Abso, double *mpo, double *Reflt, double *Trant, double *Absot, double temc, double hlr0, double hrl0, double b, int vyve, double poristo, double dpct, double htch, double hvoz, int kost, double *ete, double *kttkve, int cemve, int vtve, double *qobve, double *ktpvove, double *tevove, char *snm, int dmao, double *stchsrve, double *Tpctve, int dmkvove)
{
	int j = 2, k, f = 6, q, *nost = new int[j];
	double p, r, hf = 1e0, ra, qs, d = 0.0, **mu, qobvee, *Elr, p1=hf, p2=hf, *Evsv; for (j = 0; j < kost; j++) d = d + hf; //cout << "d = " << d << endl;
	q = 2 * kost; double *tvs = new double[f], *tbs = new double[q], *epst = new double[f], *hvi = new double[f];
	double *Rs = new double[f], *Ap = new double[f], rsf = 0.0;
	if ((!tvs) || (!tbs) || (!epst) || (!hvi) || (!Rs) || (!Ap)) { cout << snm << endl; k = getchar(); exit(1); }
	else for (j = 0; j < f; j++) { tvs[j] = 0.0; epst[j] = 0.0; hvi[j] = 0.0; Rs[j] = 0.0; Ap[j] = 0.0; }
	qobvee = opredKTPTKTochSha(qobve, ete, temc, cemve);
	p = dpct; Tpctve = opredPolTempTvKarShaFragm(Tpctve, kost, ete, kttkve, cemve, htch, hvoz, p*qobvee, temc, -hf);
	tbs = opredTempStenShaFragm(tbs, q, ktpvove, tevove, ete, kttkve, cemve, dmkvove, htch, hvoz, (hf - p)*qobvee, temc, -hf);
	p1 = b; if ((1e0 - dpct)*b <= 1e0) p2 = 1e0; else if (pow(1e0 - dpct,2e0)*b <= 1e0) p2 = p1;
	double *hlr1 = NULL, *hrl1 = NULL, *reiz = NULL, slr, srl, h = hvoz, w = p2*h, l = p1*h;
	Ap[0] = w*l; Ap[1] = h*l; Ap[2] = Ap[0]; Ap[3] = Ap[1]; Ap[4] = w*h; Ap[5] = Ap[4]; nost[0] = 0; nost[1] = 2;
	double rhlr0 = hlr0 - hrl0, *Ts = NULL, *Tss = NULL, *Tsr = NULL, *Tna = NULL;
	qs = (1e0 - dpct)*qobvee; if (qs < rhlr0) { rhlr0 = qs; hlr0 = rhlr0 + hrl0; }
	mu = opredTempLPStenSha(Ts, Tss, Tsr, Tna, temc, q, ktpvove, tevove, ete, kttkve, cemve, dmkvove, htch, hvoz, qs - rhlr0, kost, snm);
	k = 0; Ts = mu[k]; k++; Tss = mu[k]; k++; Tsr = mu[k]; k++; Tna = mu[k]; delete[]mu;
	mu = RaschVneshIzluchSha(Tran, Refl, mpo, hlr1, hrl1, kost, hlr0, hrl0, snm);
	k = 0; hlr1 = mu[k]; k++; hrl1 = mu[k]; k++; reiz = mu[k]; delete[]mu;
	double *ao = new double[dmao], *sislr = NULL, *sisrl = NULL; k = 0; slr = reiz[k]; k++; srl = reiz[k];
	if (!ao) { cout << snm << endl; k = getchar(); exit(1); } for (k = 0; k < dmao; k++) ao[k] = 0.0;
	mu = RaschSobLuchPlotTepPot(ks, mpo, Ts, Tss, Tran, Refl, Abso, slr, srl, ao, 0, snm);
	k = 0; ao = mu[k]; k++; sislr = mu[k]; k++; sisrl = mu[k]; delete[]mu;
	mu = RasLuchPloTepPot(kost, hrl1, hlr1, ao, Tran, Refl, Abso, 2, sislr, sisrl, Tsr, snm);
	k = 0; ao = mu[k]; k++; Elr = mu[k]; k++; Evsv=mu[k]; delete[]mu;
	q = 0; rsf = 0.0; r = 0.0; for (j = 0; j < (kost - 1); j++) {
		for (k = 0; k < f; k++) tvs[k] = Tpctve[j]; tvs[0] = tbs[j]; tvs[2] = tbs[j + 1]; //for (k = 0; k < f; k++) Rs[k] = Reflt[j]; Rs[0] = Refl[j]; Rs[2] = Refl[j + 1]; 
		for (k = 0; k<f; k++) epst[k]=Absot[k]; epst[0]=Abso[j]+Tran[j]; epst[2]=Abso[j+1]+Tran[j+1]; //for (k = 0; k<f; k++) epst[k] = opredKTPTKTochSha(stchsrve, ete, tvs[k], cemve); epst[0] = Abso[j]; epst[2] = Abso[j + 1];
		for (k = 0; k<f; k++) Rs[k] = 1e0-epst[k]; //for (k = 0; k<f; k++) epst[k] = 1e0-Rs[k];
		for (k = 0; k<f; k++) hvi[k] = 0.0; hvi[0] = Elr[j]; //hvi[2]=-Elr[j];
		ra = SeryeStenkiRasIzl(w, h, l, tvs, epst, hvi, Rs, Ap, nost, f); //cout << "ra ( " << j << " ) = " << ra << endl; 
		if (fabs(ra)>0.0) { rsf = ra + rsf; r = r + hf; } q = q + 2; 
	}
	delete[]Ts; delete[]Tss; delete[]Tna; delete[]Tsr; delete[]hlr1;
	delete[]hrl1; delete[]reiz; delete[]sislr; delete[]sisrl;
	delete[]Elr; delete[]Evsv; delete[]ao; delete[]tvs; delete[]tbs; delete[]epst;
	delete[]hvi; delete[]Rs; delete[]nost; delete[]Ap; if (fabs(r)>0.0) rsf = rsf / r; else rsf = 0.0; return rsf;
}
double KorrZnachVozdProsSham(double hps, double ksf, double por)
{
	int j = 0, k = 1000; double pa = 1e-3, pb = 1e0, pc, ra = fabs(pa - pb); 
	dpcts=opredKTPTKTochSha(dpctsm, etesha, etesha[vtsh], cem);
	double fa, fb, fc, tca, tcb, tcc, ka = hps*pa / por, kb = pb*hps / por, kc; //cout << "hps = " << hps << "\tksuf = " << ksf << "\tpor = " << por << endl;
	while ((ra > tocrassha) && (j < k)) { //ïîäòÿãèâàåì ïîðèñòîñòü ê çíà÷åíèþ, êîòîðîå çàäàëè èçíà÷àëüíî, âî âðåìÿ ïîäñòðîéêè ÝÊÒÏ
		pc = (pa + pb) / 2e0;
		kc = hps*pc / por;
		tcc = kc*(1e0 - pc) / pc;
		fc = (1e0 - dpcts)*kc / (kc + tcc) - por;
		ka = hps*pa / por;
		tca = ka*(1e0 - pa) / pa;
		fa = (1e0 - dpcts)*ka / (ka + tca) - por;
		kb = hps*pb / por;
		tcb = kb*(1e0 - pb) / pb;
		fb = (1e0 - dpcts)*kb / (kb + tcb) - por;
		if ((fc*fb > 0.0) && (fa*fc<0.0)) pb = pc;
		if ((fc*fa>0.0) && (fb*fc < 0.0)) pa = pc;
		j++; ra = fabs(pa - pb);
	} //ñêîððåêòèðîâàííîå çíà÷åíèå òîëùèíû âîçäóøíîé ïðîñëîéêè (ðàçìåð ïîðû), êîãäà ââåëè ïåðåìû÷êó
	return kc;
}