#include <windows.h>
#include<iostream>
using namespace std; 
HMIDIOUT handle;
enum Scale {
	A0 = 21, SA0, B0,
	C1, SC1, D1, SD1, E1, F1, SF1, G1, SG1, A1, SA1, B1,
	C2, SC2, D2, SD2, E2, F2, SF2, G2, SG2, A2, SA2, B2,
	C3, SC3, D3, SD3, E3, F3, SF3, G3, SG3, A3, SA3, B3,
	C = 60, SC, D, SD, E, F, SF, G, SG, A, SA, B,
	C5, SC5, D5, SD5, E5, F5, SF5, G5, SG5, A5, SA5, B5,
	C6, SC6, D6, SD6, E6, F6, SF6, G6, SG6, A6, SA6, B6,
	C7, SC7, D7, SD7, E7, F7, SF7, G7, SG7, A7, SA7, B7,
	C8
};
int n=0;
void S(DWORD t){
	printf("(0,%d) %d\n",t,++n);
	Sleep(t);return;
} 
void M(int m,DWORD t) {
	int volume = 0x7f;
	int voice = 0x0;
	voice = (volume << 16) + (m << 8) + 0x94;
	midiOutShortMsg(handle, voice);
	printf("(%d,%d) %d\n",voice,t,++n);
	Sleep(t);return;
}
void M2(int m1,int m2, DWORD t) {
	int volume = 0x7f;
	int voice1 = 0x0, voice2 = 0x0;
	voice1 = (volume << 16) + (m1 << 8) + 0x94;
	voice2 = (volume << 16) + (m2 << 8) + 0x94;
	midiOutShortMsg(handle, voice1);
	midiOutShortMsg(handle, voice2);
	n+=2;
	printf("(%d,%d) %d\n",voice1,0,n-1);
	printf("(%d,%d) %d\n",voice2,t,n);
	Sleep(t);return;
}
void MM(int m1, DWORD t) {
	int volume = 0x7f;
	int voice1 = 0x0, voice2 = 0x0;
	voice1 = (volume << 16) + (m1 << 8) + 0x94;
	voice2 = (volume << 16) + ((m1+12) << 8) + 0x94;
	midiOutShortMsg(handle, voice1);
	midiOutShortMsg(handle, voice2);
	n+=2;
	printf("(%d,%d) %d\n",voice1,0,n-1);
	printf("(%d,%d) %d\n",voice2,t,n);
	Sleep(t);return;
}
void MMM(int m1, DWORD t) {
	int volume = 0x7f;
	int voice1 = 0x0, voice2 = 0x0,voice3 = 0x0;
	voice1 = (volume << 16) + (m1 << 8) + 0x94;
	voice2 = (volume << 16) + ((m1+12) << 8) + 0x94;
	voice3 = (volume << 16) + ((m1+24) << 8) + 0x94;
	midiOutShortMsg(handle, voice1);
	midiOutShortMsg(handle, voice2);
	midiOutShortMsg(handle, voice3);
	n+=3;
	printf("(%d,%d) %d\n",voice1,0,n-2);
	printf("(%d,%d) %d\n",voice2,0,n-1);
	printf("(%d,%d) %d\n",voice3,t,n);
	Sleep(t);return;
}
int BPM;
DWORD P, TP, FP, PP, QP, PQP,P64;
 void sp(int a) {
	P = 60000 / a;
	TP = 2 * P;
	FP = P * 4;
	PP = P / 2;
	QP = P / 4;
	PQP = P / 8;
	P64 = P / 16;
	return;
}
int main(void)
{
	unsigned long f=midiOutOpen(&handle, 0, 0, 0, CALLBACK_NULL);
if (f)
	cout<<"ERROR:无 MIDI 播放设备";
else {
	cout << "BPM:";
	cin >> BPM;
	sp(BPM);
	
	S(PP), M2(SD, SD5, PP), M2(SD, SD5, PP), M2(SD, SD5, PP),
	M2(SD6, SD7, PP), M2(SD6, SD7, PP), M2(SD6, SD7, PP);
	M2(SD, SD5, PP), M2(SD, SD5, PP), M2(SD, SD5, PP), 
	M2(SD6, SD7, PP), M2(SD6, SD7, PP), M2(SD6, SD7, PP);
	M2(SD, SD5, PP), M2(SD6, SD7, PP), M2(SD6, SD7, PP),
	M2(SD, SD5, PP), M2(SD6, SD7, PP), M2(SD6, SD7, PP);S(PP),
	
	M(SD5, QP),M(SD6, QP),M(SD6, QP), M(SD7, QP), M(SD6, QP), M(SD7, QP),M(SC6, QP), M(SD7, QP);
	M2(B5, SG3, PQP),M(SD,PQP), M2(SD5,SD7, QP), M(B5, QP), M(SD7, QP), M(SA5, QP), M(SD7, QP),
	M2(SG5, B3, PQP), M(SG, PQP), M2(SD7,SD5 ,QP), M(G5, QP), M(SD7, QP), M(SG5, QP), M(SD7, QP);
	M2(SA5, SD, PQP), M(SA, PQP), M2(SD7, G5,QP), M(SD5, QP), M(SD7, QP), M(SD5, QP), M(SD6, QP),
	M2(G,E5,PQP),M(SA, PQP), M(SD6, QP), M(SD5, QP), M(SD6, QP), M(SC5, QP), M(SD6, QP);
	M2(B,SF, QP), M(SD6, QP), M(B, QP), M(SD6, QP), M(SA, QP), M(SD6, QP),
	M2(SG, B3, PQP), M(D, PQP), M2(SD6, F,QP), M(G, QP), M(SD6, QP), M(SG, QP), M(SD6, QP);
	M(SA, 0),M2(SD,G,QP), M(SD6, QP), M(SD, QP), M(SD5, QP), M(SD5, QP), M(SD6, QP),

	M(SD6, QP), M(SD7, QP), M(SD6, QP), M(SD7, QP), M(SC6, QP), M(SD7, QP);
	M2(B5, SG3, PQP), M(SD, PQP), M2(SD5, SD7, QP), M(B5, QP), M(SD7, QP), M(SA5, QP), M(SD7, QP),
	M2(SG5, B3, PQP), M(SG, PQP), M2(SD7, SD5, QP), M(G5, QP), M(SD7, QP), M(SG5, QP), M(SD7, QP);
	M2(SA5, SD, PQP), M(SA, PQP), M2(SD7, G5, QP), M(SD5, QP), M(SD7, QP), M(SD5, QP), M(SD6, QP),
	M2(G, E5, PQP), M(SA, PQP), M(SD6, QP), M(SD5, QP), M(SD6, QP), M(SC5, QP), M(SD6, QP);
	M(SD5, 0), M2(SG,B,QP),M(SD6, QP), M(SG5, QP), M(B5, QP), M(SD6, QP), M(SD7, QP),
	M(SD5, 0),M(SD,0),M2(G,SC5,QP), M(SD6, QP), M(G5, QP), M(SA5, QP), M(SD6, QP), M(SD7, QP);
	M(SG3, QP), M(SD, QP), M(B, QP), M(SG5, QP), M(SD5, QP), M(SD6, QP),

	M(SD6, QP), M(SD7, QP), M(SD6, QP), M(SD7, QP), M(SC6, QP), M(SD7, QP);
	M2(B5, SG2,QP), M(SD7, QP), M(B5, 0),M2(SD3,B3,QP), M(SD7, QP), M(SA5, QP), M(SD7, QP),
	M2(SG5,B2, QP), M(SD7, QP), M(G5, 0), M2(SG3,SD,QP),M(SD7, QP), M(SG5, QP), M(SD7, QP);
	M2(SA5,SD3, QP), M(SD7, QP), M(SD5, 0),M2(SA3,G,QP), M(SD7, QP), M(SD5, QP), M(SD6, QP),
	M(E5, 0),M2(G,SA,QP), M(SD6, QP), M(SD5, 0),M2(G,SA,QP), M(SD6, QP), M(SC5, QP), M(SD6, QP);
	M2(B, SG,QP), M(SD6, QP), M2(B,SG, QP), M(SD6, QP), M(SA, QP), M(SD6, QP),
	M2(SG,B3, 0),M2(D,F,QP), M(SD6, QP), M2(G,B3, 0),M2(D,F,QP) ,M(SD6, QP), M(SG, QP), M(SD6, QP);
	M(SA, 0), M2(SD3,G,QP),M(SD6, QP), M(SD, QP), M(SD5, QP), M(SD5, QP), M(SD6, QP),

	M(SD6, QP), M(SD7, QP), M(SD6, QP), M(SD7, QP), M(SC6, QP), M(SD7, QP);
	M2(B5, SG2, QP), M(SD7, QP), M(B5, 0), M2(SD3, B3, QP), M(SD7, QP), M(SA5, QP), M(SD7, QP),
	M2(SG5, B2, QP), M(SD7, QP), M(G5, 0), M2(SG3, SD, QP), M(SD7, QP), M(SG5, QP), M(SD7, QP);
	M2(SA5, SD3, QP), M(SD7, QP), M(SD5, 0), M2(SA3, G, QP), M(SD7, QP), M(SD5, QP), M(SD6, QP),
	M2(E5,SC, 0), M2(SG, SA, QP), M(SD6, QP), M2(SD5,SD, 0), M2(SG, SA, QP), M(SD6, QP), M2(SC5,E, 0), M2(SG, SA, QP), M(SD6, QP);
	M2(SD5,SD, 0), M2(SG, B, QP), M(SD6, QP), M(SG5, QP), M(B5, QP), M(SD6, QP), M(SD7, QP),
	M2(SD5, SD3,0), M2(SD, G, QP), M(SD6, QP), M(G5, QP), M(SA5, QP), M(SD6, QP), M(SD7, QP);
	S(PP), M(SG2, QP), M(B3, QP), M(SD, QP), M(SG, QP),
	M(SD5, QP), M(SG5, QP), M(B5, QP), M(SD6, QP), M(SG6, QP), S(PP);
	
	S(P), M(B, QP), M2(G, SA, QP), M(B, QP), M2(SF, SA, QP), M(B, QP), M2(F,SG,QP), M(B, QP), M2(E,SG,QP);
	
	M(SC5, PQP), M(B, PQP), M(SA, PQP), M(B, PQP), M(SF, 0), M2(B3, SD, QP), M(SF6, QP), M2(B, SF3, 0), M2(SD, SF, QP), M(SF6, QP),
	M(SD5, PQP), M(SC5, PQP), M(C5, PQP), M(SC5, PQP), M(SF, 0), M2(SA3, E, QP), M(SF6, QP), M2(SC5, SF3, 0), M2(E, SF, QP), M(SF6, QP);
	M(E5, PQP), M(SD5, PQP), M(D5, PQP), M(SD5, PQP), M(B, 0), M2(B3, SD, QP), M(SF6, QP), M(SD5, QP), M2(B, D5, QP),
	M(SD5, QP), M2(SA, SC5, QP), M(SD5, QP), M2(SA, C5, QP), M(SD5, QP), M2(SG, B, QP);

	M(F5, PQP), M(SD5, PQP), M(D5, PQP), M(SD5, PQP), M(SA, 0), M2(SD, SF, QP), M(SA6, QP), M2(SD5, SA3, 0), M2(SF, SA, QP), M(SA6, QP),
	M(SF5, PQP), M(F5, PQP), M(SD5, PQP), M(F5, PQP), M(SA, 0), M2(D, SG, QP), M(SA6, QP), M2(F5, SA3, 0), M2(SG, SA, QP), M(SA6, QP);
	M(SG5, PQP), M(SF5, PQP), M(F5, PQP), M(SF5, PQP), M(SD5, 0), M2(SD, SF, QP), M(SA6, QP), M(SF5, QP), M2(SC5, F5, QP);
	M(SF5, QP), M2(SC5, E5, QP), M(SF5, QP), M2(C5, SD5, QP), M(SF5, QP), M2(B, SD, QP);

	M(SG5, PQP), M(SF5, PQP), M(F5, PQP), M(SF5, PQP), M(SC5, 0), M2(SF, SA, QP), M(SC7, QP), M2(SF5, SC, 0), M2(SA, SC5, QP), M(SC7, QP);
	M(SA5, PQP), M(SG5, PQP), M(G5, PQP), M(SG5, PQP), M(SC5, 0), M2(F, B, QP), M(SC7, QP), M2(SG5, SC, 0), M2(B, SC5, QP), M(SC7, QP);
	M2(SA5, SF5, QP), M2(B5, SG5, QP), M2(SF, SC5, PQP), M(SA5, PQP), M2(SA6, SC7, QP), M2(B5, SG5, QP), M2(SA5, SF5, QP),
	M2(SG5, B, QP), M2(SA5, SC5, QP), M2(B3, B5, PQP), M(SD5, PQP), M2(SD6, B6, QP), M2(SA5, SC5, QP), M2(SG5, B, QP);
	M2(SF5, SA, QP), M2(SG5, B, QP), M2(SC, SA5, PQP), M(SC5, PQP), M2(SC6, SA6, QP), M2(SG5, B, QP), M2(SF5, SA, QP),
	M2(F5, SG, QP), M2(SF5, SA, QP), M2(SC, SG5, PQP), M(B, PQP), M2(B5, SG6, QP), M2(SD5, SA, QP), M2(SF5, SG, QP);
	M(SF5, 0), M2(SF3, SA, QP), M2(SA5, SF6, QP), M(SF, QP), M(SF5, QP), M(G, QP), M(G5, QP),
	
	M(SG, QP), M(SG5, QP), M(SG6, 0), M2(E, SG, QP), M(SG5, QP), M(SG6, 0), M2(SD, SG, QP), M(SF5, QP);
	M(SG6, 0), M2(SC, SG, QP), M(E5, QP), M2(SF7, SD5, QP), M(SG5, QP), M2(E7, SC5, QP), M(SG5, QP),
	M(SD7, 0), M2(SG3, C5, QP), M(SG5, QP), M2(SC7, SA, QP), M(SG5, QP), M2(SD7, C5, QP), M(SG5, QP);
	M(E7, 0), M2(SC, SC5, QP), M(SG5, QP), M2(SC7, E5, QP), M(SG5, QP), M(G, QP), M(G5, QP),
	
	M(SF, QP), M(SF5, QP), M(SF6, 0), M2(SD, SF, QP), M(SF5, QP), M(SF6, 0), M2(SD, SF, QP), M(E5, QP);
	M(SF6, 0), M2(B3, SF, QP), M(SD5, QP), M2(E7, SC5, QP), M(SF5, QP), M2(SD7, B, QP), M(SF5, QP),
	M(SC7, 0), M2(SF3, SA, QP), M(SF5, QP), M2(B6, SG, QP), M(SF5, QP), M2(SC7, SA, QP), M(SF5, QP);
	M(SD7, 0), M2(B3, B, QP), M(SF5, QP), M2(B6, SD5, QP), M(SF5, QP), M(D, QP), M(D5, QP),
	
	M(SD, QP), M(SD5, QP), M(SD6, 0), M2(G3, SD, QP), M(SD5, QP), M(SD6, 0), M2(SG3, F, QP), M(D5, QP);
	M(SD6, 0), M2(SA3, G, QP), M(SC5, QP), M(SD6, 0), M2(SA3, G, QP), M(SC5, QP), M(SD6, 0) ,M2(B3, SG, QP), M(B, QP),
	M2(E5, E6, 0), M2(SC, SA, QP), M2(SA5, SD6, QP), M2(SD5, SD6, QP), M2(E5, B5, QP), M2(B, SA5, 0), M2(D, F, QP), M2(F5, SG5, QP);
	M2(SA, G5, 0), M2(SD, G, QP), M2(SD5, SA5, QP), M2(G5, B5, QP), M2(SD5, SA5, QP), M(D5, QP), M(D6, QP),
	
	M(SD5, QP), M(SD6, QP), M(SD7, 0), M2(G, SD5, QP), M(SD6, QP), M(SD7, 0), M2(SG, F5, QP), M(D6, QP);
	M(SD7, 0), M2(SA, G5, QP), M(SC6, QP), M(SD7, 0), M2(SA, G5, QP), M(SC6, QP), M(SD7, 0), M2(B, SG5, QP), M(B5, QP),
	M2(E6, E7, 0), M2(SC5, A5, QP), M2(SA6, SD7, QP), M2(SD6, SD7, QP), M2(E6, B6, QP), M2(B5, SA6, 0), M2(D5, F5, QP), M2(F6, SG6, QP);
	M2(SA5, G6, 0), M2(SD5, G5, QP), M2(SD6, SA6, QP), M(D5, QP), M(D6, QP), M(SD5, QP), M(SD6, QP),
	
	M(SD7, QP), M(SD6, QP), M(SD5, QP), M(SD6, QP), M(E5, QP), M(E6, QP);
	M(SD7, QP), M(SD6, QP), M(E5, QP), M(E6, QP), M(F5, QP), M(F6, QP),
	M(SD7, QP), M(SD6, QP), M(SF6, QP), M(SF7, QP), M(SD7, QP), M(SD6, QP);
	M(SF5, QP), M(SF6, QP), M(SD7, QP), M(SD6, QP), M(SG5, QP), M(SG6, QP),
	M(SD7, QP), M(A5, QP), M(SD7, QP), M(SA5, QP), M(SD7, QP), M(B5, QP);
	M(SD7, QP), M(C6, QP), M(SD7, QP), M(SC6, QP), M(SD7, QP), M(D6, QP),
	M(SD7, QP), M(SD6, QP), M(SD7, QP), M(SD6, QP), M(SD7, QP), M(SD6, QP);
	M(SD7, QP), M(SD6, QP), M(SD7, QP), M(SD6, QP), M(SD7, QP), M(SD6, QP),
	M(SD7, QP), M(SD6, QP), M(SD5, QP), M(SD6, QP), M(SD7, QP), M(SD6, QP);
	
	M(SD5, QP), M(SD6, QP), M(SD7, QP), M(SD6, QP), M2(SD5, SD, QP), M(SD6, QP),
	M2(SD7, SD5, QP), M(SD6, QP), M(SD5, QP), M(SD6, QP), M2(SD7, SC5, QP), M(SD6, QP);
	M2(SG3,SD5,PQP), M(B, PQP),M(SD6, QP), M2(SD7,B, QP), M(SD6, QP), M2(SD5, SA, QP), M(SD6, QP),
	M2(SD7,B3,PQP), M(SG,PQP),M(SD6, QP), M2(SD5, G,QP), M(SD6, QP), M2(SD7, SG,QP), M(SD6, QP);
	M2(SD5, G,PQP), M(SA, PQP), M(SD6, QP), M2(SD7, SD, QP), M(SD6, QP), M2(SD5, SD, QP), M(SD6, QP),
	M2(G3, SD7, PQP),M(E, PQP),  M(SD6, QP), M2(SD5, SD, QP), M(SD6, QP), M2(SD7, SC, QP), M(SD6, QP);
	M2(SD5, SG3, PQP), M(B3, PQP), M(SD6, QP), M2(SD7, B3, QP), M(SD6, QP), M2(SD5, SA3, QP), M(SD6, QP),
	M2(E3, SD7, PQP), M(SG3, PQP), M(SD6, QP), M2(SD5, G3, QP), M(SD6, QP), M2(SD7, SG3, QP), M(SD6, QP);
	M(SD5, 0), M2(G3, SA3, QP), M(SD6, QP), M2(SD7, SD3, QP), M(SD6, QP), M(SD5, QP), M(SD6, PQP), M(SD, PQP);
	M2(SD7, SD5, QP), M(SD6, QP), M2(SD5, SC5, QP), M(SD6, QP), M(SD7, QP), M(SD6, QP);
	M2(SG3, SD5, PQP), M(B, PQP), M(SD6, QP), M2(SD7, B, QP), M(SD6, QP), M2(SD5, SA, QP), M(SD6, QP),
	M2(SD7, B3, PQP), M(SG, PQP), M(SD6, QP), M2(SD5, G, QP), M(SD6, QP), M2(SD7, SG, QP), M(SD6, QP);
	M2(SD5, G, PQP), M(SA, PQP), M(SD6, QP), M2(SD7, SD, QP), M(SD6, QP), M(SD5, QP), M(SD6, QP),
	M2(SD5, SC, 0), M2(SA, SG, QP), M(SD6, QP), M2(SD5, SD, 0), M2(SG,SA,QP),M(SD6, QP), M2(SC5, SG, 0),M2(E,SA,QP), M(SD6, QP);
	M2(SD5, SD, 0), M2(SG, B, QP), M(SD6, QP), M(SG5, QP), M(B5, QP), M(SD6, QP), M(SD7, QP),
	M2(SD5, SD, 0), M2(G, SC5, QP), M(SD6, QP), M(G5, QP), M(SA5, QP), M(SD6, QP), M(SD7, QP);
	M(SG3, QP), M(SD, QP), M(B, QP), M(SG5, QP),
	
	M(SD5, PP / 3), M(SD6, PP / 3), M(SD6, PP / 3), M(SD6, PP / 3), M(SD6, PP / 3), M(SD7, PP / 3), M(SD6, PP / 3), M(SD6, PP / 3), M(SD7, PP / 3), M(SC6, PP / 3), M(SC6, PP / 3), M(SC7, PP / 3);
	M2(B5, SG2, PP / 3), M(B5, PP / 3), M(B6, PP / 3), M2(SD3, B3, 0), M(B5, PP / 3), M(B5, PP / 3), M(B6, PP / 3), M2(SD3, B3, 0), M(SA5, PP / 3), M(SA5, PP / 3), M(SA6, PP / 3),
	M2(SG5, B2, PP / 3), M(SG5, PP / 3), M(SG6, PP / 3), M2(SG3, SD, 0), M(G5, PP / 3), M(G5, PP / 3), M(G6, PP / 3), M2(SD, SG3, 0), M(SG5, PP / 3), M(SG5, PP / 3), M(SG6, PP / 3);
	M2(SA5, SD3, PP / 3), M(SA5, PP / 3), M(SA6, PP / 3), M2(SA3, G, 0), M(SD5, PP / 3), M(SD5, PP / 3), M(SD6, PP / 3), M2(SA3, G, 0), M(SD5, PP / 3), M(SD5, PP / 3), M(SD6, PP / 3),
	M2(E5, G3, PP / 3), M(E5, PP / 3), M(E6, PP / 3), M2(SA, SD, 0), M(SD5, PP / 3), M(SD5, PP / 3), M(SD6, PP / 3), M2(SD, SA, 0), M(SC5, PP / 3), M(SC5, PP / 3), M(SC6, PP / 3);
	M2(B, SG3, PP / 3), M(B, PP / 3), M(B5, PP / 3), M(B, 0), M2(SD, SG, PP / 3), M(B, PP / 3), M(B5, PP / 3), M(SA, 0), M2(SD, SG, PP / 3), M(SA, PP / 3), M(SA5, PP / 3),
	M2(B3, SG, PP / 3), M(SG, PP / 3), M(SG5, PP / 3), M(G, 0), M2(D, F, PP / 3), M(G, PP / 3), M(G5, PP / 3), M(SG, 0), M2(D, F, PP / 3), M(SG, PP / 3), M(SG5, PP / 3);
	M2(SA, SD3, PP / 3), M(SA, PP / 3), M(SA5, PP / 3), M(SD, 0), M2(SA3, G, PP / 3), M(SD, PP / 3), M(SD5, PP / 3), M(SD5, PP / 3), M(SD5, PP / 3), M(SD5, PP / 3),
	M(SD6, PP / 3), M(SD6, PP / 3), M(SD7, PP / 3), M(SD6, PP / 3), M(SD6, PP / 3), M(SD7, PP / 3), M(SC6, PP / 3), M(SC6, PP / 3), M(SC7, PP / 3);
	M2(B5, SG2, PP / 3), M(B5, PP / 3), M(B6, PP / 3), M2(SD3, B3, 0), M(B5, PP / 3), M(B5, PP / 3), M(B6, PP / 3), M2(SD3, B3, 0), M(SA5, PP / 3), M(SA5, PP / 3), M(SA6, PP / 3),
	M2(SG5, B2, PP / 3), M(SG5, PP / 3), M(SG6, PP / 3), M2(SG3, SD, 0), M(G5, PP / 3), M(G5, PP / 3), M(G6, PP / 3), M2(SD, SG3, 0), M(SG5, PP / 3), M(SG5, PP / 3), M(SG6, PP / 3);
	M2(SA5, SD3, PP / 3), M(SA5, PP / 3), M(SA6, PP / 3), M2(SA3, G, 0), M(SD5, PP / 3), M(SD5, PP / 3), M(SD6, PP / 3), M2(SA, G, 0), M(SD5, PP / 3), M(SD5, PP / 3), M(SD6, PP / 3),
	M(E5,0),M2(SG, B, PP / 3), M(E5, PP / 3), M(E6, PP / 3), M2(SF, SA, 0), M(SD5, PP / 3), M(SD5, PP / 3), M(SD6, PP / 3), M2(E, SG, 0), M(SC5, PP / 3), M(SC5, PP / 3), M(SC6, PP / 3);
	
	M2(SD, SD5, PQP), M(SG,PP/3-PQP),M(SD5, PP / 6), M(SD6, PP / 6), M(E5, PP / 3), M(E5, PP / 3), M(SD6, PP / 3), M(F5, PP / 3), M(F5, PP / 3), M(SD6, PP / 3),
	M(SF5, PP / 3), M(SF5, PP / 3), M(SD6, PP / 3), M(G5, PP / 3), M(G5, PP / 3), M(SD6, PP / 3), M(SG5, PP / 3), M(SG5, PP / 3), M(SD6, PP / 3);
	M2(SD3, SC, 0), M2(A5, G, PP / 3), M(A5, PP / 3), M(SD6, PP / 3), M(SA5, PP / 3), M(SA5, PP / 3), M(SD6, PP / 3), M(B5, PP / 3), M(B5, PP / 3), M(SD6, PP / 3),
	M(C6, PP / 3), M(C6, PP / 3), M(SD6, PP / 3), M(SC6, PP / 3), M(SC6, PP / 3), M(SD6, PP / 3), M(D6, PP / 3), M(D6, PP / 3), M(SD6, PP / 3);
	M(SG2,0),M2(SD3, B3, 0), M2(SG, SD6, PP / 3), M(SD6, PP / 3), M(SD7, PP / 3), M(E6, PP / 3), M(E6, PP / 3), M(SD7, PP / 3), M(F6, PP / 3), M(F6, PP / 3), M(SD7, PP / 3),
	M(SF6, PP / 3), M(SF6, PP / 3), M(SD7, PP / 3), M(G6, PP / 3), M(G6, PP / 3), M(SD7, PP / 3), M(SG6, PP / 3), M(SG6, PP / 3), M(SD7, PP / 3);
	S(P);

	M2(B, SG, QP), M2(SA, G, QP), M(SF, 0), M2(B, A, QP), M(F, 0), M2(B, SG, QP), M(E, 0), M2(B, G, QP), M(SD, 0), M2(B, SF, QP), M(D, 0), M2(B, F, QP), M(SC, 0), M2(B, E, QP),
	M(SC5, PQP), M(B, PQP), M(SA, PQP), M(B, PQP), M2(B3, SD, 0), M(SF, PQP), M(SF5, PQP), M(SF5, PQP), M(SF5, PQP), M2(SF3, SD, 0), M2(B, SF, PQP), M(B5, PQP), M(B5, PQP), M(B5, PQP),
	M(SC5, PQP), M(SC6, PQP), M(SC6, PQP), M(SC6, PQP), M2(SA3, E, 0), M(SF5, PQP), M(SF6, PQP), M(SF6, PQP), M(SF6, PQP), M2(SF3, SA3, 0), M2(SC6, SF, PP / 3), M2(SF6, SC7, PP / 3), M2(SF6, SC7, PP / 3);
	M2(SD6, B2, PP / 3), M2(SF6, SD7, PP / 3), M2(SF6, SD7, PP / 3), M(B5, 0), M2(SF3, SD,PP),M2(B, SD5, QP), M(D5, QP),
	M(SA, 0), M2(SD5, SC5, QP), M(A, 0), M2(C5, SD5, QP), M(SG, 0), M2(B, SC5, QP), M(G, 0), M2(SA, SC5, QP), M(SF, 0), M2(SC5, A, QP), M(F, 0), M2(SC5, SG, QP);
	M(F5, PQP), M(SD5, PQP), M(D5, PQP), M(SD5, PQP), M2(SD, SF, 0), M(SA, PQP), M(SA5, PQP), M(SA5, PQP), M(SA5, PQP), M2(SA3, SF, 0), M2(SD5, SA, PQP), M(SD6, PQP), M(SD6, PQP), M(SD6, PQP),
	M(F5, PQP), M(F6, PQP), M(F6, PQP), M(F6, PQP), M2(D, SG, 0), M(SA5, PQP), M(SA6, PQP), M(SA6, PQP), M(SA6, PQP), M2(SA3, D, 0), M2(F6, SA, PP / 3), M2(SA6, E7, PP / 3), M2(SA6, E7, PP / 3);
	M2(SF6, SD2, PP / 3), M2(SA6, SF7, PP / 3), M2(SA6, SF7, PP / 3), M(SD6, 0), M2(SA3, SF, PP), M2(SD5, SF5, QP), M2(D5, F5, QP),
	M(SF5, 0), M2(E5, SC5, QP), M(SF5, 0), M2(C5, SD5, QP), M(SF5, 0), M2(B, D5, QP), M(SF5, 0), M2(SA, SC5, QP), M(SF5, 0), M2(C5, A, QP), M(SF5, 0), M2(B, SG, QP);
	M(SG5, PQP), M(SF5, PQP), M(F5, PQP), M(SF5, PQP), M2(SC5, SF, 0), M(SA, PQP), M(SC5, PQP), M(SC5, PQP), M(SC5, PQP), M2(SC, SA, 0), M2(SC5, SF5, PQP), M(SF6, PQP), M(SF6, PQP), M(SF6, PQP),
	M(SG5, PQP), M(SG6, PQP), M(SG6, PQP), M(SG6, PQP), M2(F, B, 0), M(SC6, PP / 3), M2(SG6, SC7, PP / 3), M2(SG6, SC7, PP / 3), M2(SC, F, 0), M(SC5, 0), M2(SG6, SC7, PP / 3), M2(SG6, SC7, PP / 3), M2(SG6, SC7, PP / 3);
	
	M(SF, 0), M2(SA6, SC7, PQP), M(SD7, PQP), M2(A6, SC7, PQP), M(SD7, PQP), M2(SF5, SA5, 0), M2(SG6, SC7, PQP), M(SD7, PQP), M2(SG5, B5, 0), M2(G6, SC7, PQP), M(SD7, PQP), M2(SA5, SC6, 0), M2(SF6, SC7, PQP), M(SD7, PQP), M(SC7, PQP), M(SD7, PQP),
	M(B3, 0), M2(SG6, B6, PQP), M(SC7, PQP), M2(G6, B6, PQP), M(SC7, PQP), M2(B, SG5, 0), M2(SF6, B6, PQP), M(SC7, PQP), M2(SC5, SA5, 0), M2(E6, B6, PQP), M(SC7, PQP), M2(SD5, B6, 0), M2(SD6, B6, PQP), M(SC7, PQP), M(B6, PQP), M(SC7, PQP);	
	M(SD, 0), M2(SF6, SA6, PQP), M(B6, PQP), M2(F6, SA6, PQP), M(B6, PQP), M2(SA, SF5, 0), M2(SC6, SA6, PQP), M(B6, PQP), M2(B, SG5, 0), M2(D6, SA6, PQP), M(B6, PQP), M2(SC5, SA5, 0), M2(SC6, SA6, PQP), M(B6, PQP), M(SA6, PQP), M(B6, PQP),
	M(SD, 0), M2(E6, SG6, PQP), M(SA6, PQP), M2(SD6, SG6, PQP), M(SA6, PQP), M2(SG, F5, 0), M2(D6, SG6, PQP), M(SA6, PQP), M2(SA, SF5, 0), M2(SC6, SG6, PQP), M(SA6, PQP), M2(B, SG5, 0), M2(B5, SG6, PQP), M(SD6, PQP), M(E6, PQP), M(F6, PQP);
	M2(SF, SC5, 0), M2(SA5, SF6, PQP), M(SG6, PQP), M(SF6, PQP), M(SG6, PQP), M(SF5, PQP), M(SF6, PQP), M(SG6, PQP), M(SF6, PQP), M(G5, PQP), M(G6, PQP), M(SG6, PQP), M(G6, PQP),
	M(SG5, PQP), M(SG6, PQP), M(A6, PQP), M(SG6, PQP), M2(E, SG5, 0), M(SG6, PQP), M(SA6, PQP), M(SG6, PQP), M(SA6, PQP), M2(SD, SF5, 0), M(SG6, PQP), M(SA6, PQP), M(SG6, PQP), M(SA6, PQP);
	M2(E, SG6, PQP), M2(SA6, G5, PQP), M(SG6, PQP), M(SA6, PQP), M2(SD, SG6, PQP), M2(SF5, SA6, PQP), M(SG6, PQP), M(SA6, PQP);
	
	M2(SG6, SC, PQP), M2(A6, E5, PQP), M(SG6,PQP),M(A6,PQP),M2(SG6,SF7,0),M(SD6,PQP), M(A6,PQP),M(SG6, PQP), M(A6, PQP), M2(SG6, E7, 0), M(SC6, PQP), M(A6, PQP), M(SG6, PQP), M(A6, PQP),
	M(SD7,0),M2(SG6, SG, PQP), M2(A6, C5, PQP), M(SG6, PQP), M(A6, PQP), M2(SG6, SC7, 0), M(SA5, PQP), M(A6, PQP), M(SG6, PQP), M(A6, PQP), M2(SG6, SD7, 0), M(B5, PQP), M(A6, PQP), M(SG6, PQP), M(A6, PQP);
	M2(E7,SG6,0),M2(SC5,SC6, PQP), M(A6, PQP), M(SG6, PQP), M(A6, PQP),M(E6,0),M2(SG6,SC7,PP),M(G5,PQP),M(G6,PQP),M(A6,PQP),M(G6,PQP),
	M(SF5,PQP),M(SF6,PQP),M(SG6,PQP),M(SF6,PQP),M2(SD, SF6, PQP), M2(SG6, SF5, PQP), M(SF6, PQP), M(SG6, PQP), M2(SC, SF6, PQP), M2(E5, SG6, PQP), M(SF6, PQP), M(SG6, PQP);
	
	M2(SF6, B3, PQP), M2(SG6, SD5, PQP), M(SF6,PQP),M(SG6,PQP),M2(SF6,E7,0),M(SC6,PQP), M(SG6,PQP),M(SF6, PQP), M(SG6, PQP), M2(SF6, SD7, 0), M(B5, PQP), M(SG6, PQP), M(SF6, PQP), M(SG6, PQP),
	M(SC7,0),M2(SF6, SF, PQP), M2(SG6, SA5, PQP), M(SF6, PQP), M(SG6, PQP), M2(SF6, B6, 0), M(SG5, PQP), M(SG6, PQP), M(SF6, PQP), M(SG6, PQP), M2(SF6, SC7, 0), M(SA5, PQP), M(SG6, PQP), M(SF6, PQP), M(SG6, PQP);
	M2(SD7,SF6,0),M2(B5,B, PQP), M(SG6, PQP), M(SF6, PQP), M(SG6, PQP),M(SD6,0),M2(SF6,B6,PP),M(D5,PQP),M(D6,PQP),M(SD6,PQP),M(D6,PQP),
	M(SD5,PQP),M(SD6,PQP),M(E6,PQP),M(SD6,PQP),M2(E6,SD5,0),M2(G,SD,PQP),M(SD6,PQP),M(E6,PQP),M(SD6,PQP),M2(E6,D5,0),M2(SG,F,PQP),M(SD6,PQP),M(E6,PQP),M(SD6,PQP);
	M2(G,E6,QP/3),M(SD6,PQP/3),M(SA,PQP/3),M(D6,QP/3),M2(SD6,SC5,QP/3),M(E6,QP/3),M(F6,QP/3),M(SF6,QP/3),M(G6,QP/3),M(SG6,QP/3),M(A6,QP/3),M(SA6,QP/3),M(B6,QP/3),M(C7,PQP),M(SC7,PQP),M(D7,PQP),M(SD7,PQP),
	M2(E7,SG,PQP),M2(SF7,B,PQP),M2(E7,E5,PQP),M(SD7,PQP),M(D7,P/11),M(SC7,P/11),M(C7,P/11),M(B6,P/11),M(SA6,P/11),M(A6,P/11),M(SG6,P/11),M(G6,P/11),M(SF6,P/11),M(F6,P/11),M(E6,P/11);
	
	M2(SD6,SD,PQP),M(G5,PP-PQP),M(SA,PQP),M(SA5,PQP),M(B5,PQP),M(SA5,PQP),M(D5,PQP),M(D6,PQP),M(SD6,PQP),M(D6,PQP),
	M(SD5,PQP),M(SD6,PQP),M(E6,PQP),M(SD6,PQP),M2(SD,G,0),M2(E6,SD5,PQP),M(SD6,PQP),M(E6,PQP),M(SD6,PQP),M2(F,SG,0),M2(E6,D5,PQP),M(SD6,PQP),M(E6,PQP),M(SD6,PQP);
	M2(G,E6,QP/3),M(SD6,PQP/3),M(SA,PQP/3),M(D6,QP/3),M2(SD6,SC5,QP/3),M(E6,QP/3),M(F6,QP/3),M(SF6,QP/3),M(G6,QP/3),M(SG6,QP/3),M(A6,QP/3),M(SA6,QP/3),M(B6,QP/3),M(C7,PQP),M(SC7,PQP),M(D7,PQP),M(SD7,PQP),
	M2(E7,SG,PQP),M2(SF7,B,PQP),M2(E7,E5,PQP),M(SD7,PQP),M(D7,P/11),M(SC7,P/11),M(C7,P/11),M(B6,P/11),M(SA6,P/11),M(A6,P/11),M(SG6,P/11),M(G6,P/11),M(SF6,P/11),M(F6,P/11),M(E6,P/11);
	M2(SD,SD6,QP/3),M(E6,PQP/3),M(SA,PQP/3),M(SD6,QP/3),M2(D6,G5,QP/3),M(SD6,QP/3),M(E6,QP/3),M(F6,QP/3),M(SF6,QP/3),M(G6,QP/3),M(SG6,QP/3),M(A6,QP/3),M(SA6,QP/3),M(B6,PQP),M(C7,PQP),M(SC7,PQP),M(D7,PQP),
	M2(B6,SD7,PQP),M2(E7,B,PQP),M(SF7,PQP),M(E7,PQP),M(SD7,QP/3),M(D7,QP/3),M(SC7,QP/3),M(C7,QP/3),M(B6,QP/3),M(SA6,QP/3),M(A6,QP/3),M(SG6,QP/3),M(G6,QP/3),M(SF6,QP/3),M(F6,QP/3),M(E6,QP/3);
	
	M2(SD6,SD3,P/15),M(E6,PQP*7/15),M(G,PQP/15),M(SD6,P/15),M(D6,P/15),M(SD6,P/15),M(E6,P/15),M(F6,P/15),M(SF6,P/15),M(G6,P/15),M(SG6,P/15),M(A6,P/15),M(SA6,P/15),M(B6,P/15),M(C7,P/15),M(SC7,P/15),
	M(D7,P/15),M(SD7,P/15),M(E7,P/15),M(SF7,P/15),M(E7,P/15),M(SD7,P/15),M(D7,P/15),M(SD7,P/30),M2(SG2,B3,P/30),M(D7,P/15),M(SC7,P/15),M(C7,P/15),M(SC7,P/15),M(C7,P/15),M(B6,P/15),M(SA6,P/15),
	M(B6,P/15),M(SA6,P/15),M(A6,P/15),M(SG6,P/15),M(A6,P/15),M(SG6,P/15),M(G6,P/15),M(SF6,P/15),M(G6,P/15),M(SF6,P/15),M(F6,P/15),M(E6,P/15),M(G6,P/15),M(E6,P/15),M(SD6,P/15);
	M(D6,P/13),M(SD6,P/13),M(D6,P/13),M(SC6,P/13),M(C6,P/13),M(SC6,P/13),M(C6,P/13),M(B5,P/13),M(SA5,P/13),M(B5,P/13),M(SA5,P/13),M(A5,P/13),M(SG5,P/13),
	M(A5,P/13),M(SG5,P/13),M(G5,P/13),M(SF5,P/13),M(G5,P/13),M(SF5,P/13),M(F5,P/13),M(E5,P/13),M(SF5,P/13),M(E5,P/13),M(SD5,P/13),M(D5,P/13),M(SD5,P/13),
	M(D5,P/14),M(SC5,P/14),M(C5,P/14),M(SC5,P/14),M(C5,P/14),M(B,P/14),M(SA,P/14),M(B,P/14),M(SA,P/14),M(A,P/14),M(SG,P/14),M(A,P/14),M(SF,P/14),M(G,P/14);
	M(SF,PQP),M(G,PQP),M(SF,PQP),M(F,PQP),M2(G2,SA3,0),M2(SC,E,P/10),M(D,P/10),M(E,P/10),M(SD,P/10),M(F,P/10),M(E,P/10),M(SF,P/10),M(F,P/10),M(G,P/10),M(SF,P/10),
	M(SG,P/10),M(G,P/10),M(A,P/10),M(SG,P/10),M(SA,P/10),M(A,P/10),M(B,P/10),M(SA,P/10),M(C5,P/10),M(B,P/10),M(SC5,PQP),M(C5,PQP),M(D5,PQP),M(SC5,PQP);
	M(SD5,PQP),M(D5,PQP),M(E5,PQP),M(SD5,PQP),M(F5,PQP),M(E5,PQP),M(SF5,PQP),M(F5,PQP),M(G5,PQP),M(SF5,PQP),M(SG5,PQP),M(G5,PQP),
	M(A5,PQP),M(SG5,PQP),M(SA5,PQP),M(A5,PQP),M(B5,PQP),M(SA5,PQP),M(C6,PQP),M(B5,PQP),M(SC6,PQP),M(C6,PQP),M(D6,PQP),M(SC6,PQP);
	M(SD6,PQP),M(D6,PQP),M(E6,PQP),M(SD6,PQP),M(F6,PQP),M(E6,PQP),M(SF6,PQP),M(F6,PQP),M(G6,PQP),M(SF6,PQP),M(SG6,PQP),M(G6,PQP),
	M(A6,PQP),M(SG6,PQP),M(SA6,PQP),M(A6,PQP),M(B6,PQP),M(SA6,PQP),M(C7,PQP),M(B6,PQP),M(SC7,PQP),M(C7,PQP),M(D7,PQP),M(SC7,PQP);
	M(SD7,PQP),M(D7,PQP),M(E7,PQP),M(D7,PQP),M(SD7,PQP),M(D7,PQP),M(E7,PQP),M(D7,PQP),M(SD7,PQP),M(D7,PQP),M(E7,PQP),M(D7,PQP),
	M(SD7,PQP),M(D7,PQP),M(E7,PQP),M(D7,PQP),M(SD7,PQP),M(D7,PQP),M(E7,PQP),M(D7,PQP),M(SD7,PQP),M(D7,PQP),M(E7,PQP),M(D7,PQP);
	M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),
	M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SD7,P);
	
	M(SD5,PP),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SC6,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP);
	M(SG,0),M2(SD7,SD6,PQP),M2(E7,B5,PQP),M(SD7,PQP),M(E7,PQP),M(B5,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SA5,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),
	M(B,0),M2(SD7,SD6,PQP),M2(E7,SG5,PQP),M(SD7,PQP),M(E7,PQP),M(G6,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SG5,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP);
	M(G5,0),M2(SD7,SD6,PQP),M2(E7,SA5,PQP),M(SD7,PQP),M(E7,PQP),M(SD5,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SD5,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),
	M(G,0),M2(SD7,SD6,PQP),M2(E7,SA,PQP),M2(SD7,E6,PQP),M(E7,PQP),M(SD5,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SC5,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP);
	M2(SG,B,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M2(SG,B,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M2(SF,SA,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),
	M2(E,SG,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(G,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SG,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP);
	M2(G,SA,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SD,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M2(SD7,SD6,PQP),M(E7,PQP),M(SD,0),M(SD7,PQP),M(E7,PQP),
	M(SD5,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SD5,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP),M(SC5,0),M2(SD7,SD6,PQP),M(E7,PQP),M(SD7,PQP),M(E7,PQP);
	M2(SD7,SG3,PQP),M2(E7,B,PQP),M(SD7,PQP),M(SD6,PQP),M2(SD6,B,PQP),M(E6,PQP),M(SD6,PQP),M(SD5,PQP),M2(SD6,SA,PP/3),M(E6,PP/3),M(SD6,PP/3),
	M2(B3,SG,0),M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(SD6,PQP),M2(SD6,G,PQP),M(E6,PQP),M(SD6,PQP),M(SD5,PQP),M2(SD6,SG,PP/3),M(E6,PP/3),M(SD6,PP/3);
	M2(SD7,G,PQP),M2(E7,SA,PQP),M(SD7,PQP),M(SD6,PQP),M2(SD6,SD,PQP),M(E6,PQP),M(SD6,PQP),M(SD5,PQP),M2(SD6,SD,PP/3),M(E6,PP/3),M(SD6,PP/3),
	M2(B3,SG,0),M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(SD6,PQP),M2(C,G,0),M(SD6,PQP),M(E6,PQP),M(SD6,PQP),M(SD5,PQP),M2(SC,E,0),M(SD6,PP/3),M(E6,PP/3),M(SD6,PP/3);
	M2(SD7,SD,PQP),M(E7,PQP),M(SD7,PQP),M(SD6,PQP),M2(B5,SG6,QP),M2(SD6,B6,QP),M2(SG5,SD6,PP),M2(SD7,SD,PQP),M(E7,PQP),M(SD7,PQP),M(SD6,PQP),M2(SA5,G6,QP),M2(SC6,SA6,QP),M2(G5,SD6,PP);M(SG3,PP),M(SD,P64),M(B,P64),M(SG5,PQP+QP),
	M(SD5,PQP),M(SD6,PQP),M(E6,PQP),M(SD6,PQP),
	M(SD6,PQP),M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(SD6,PQP),M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(SC6,PQP),M(SC7,PQP),M(SD7,PQP),M(SC7,PQP);
	M(B5,0),M2(SG1,SG2,PQP),M(B6,PQP),M(SC7,PQP),M(B6,PQP),M2(B5,SD3,0),M2(B3,SD,PQP),M(B6,PQP),M(SC7,PQP),M(B6,PQP),M2(SA5,SA3,0),M2(B3,SD,PQP),M(SA6,PQP),M(B6,PQP),M(SA6,PQP),
	M(SG5,0),M2(B1,B2,PQP),M(SG6,PQP),M(SA6,PQP),M(SG6,PQP),M2(G5,SD3,0),M2(B3,SD,PQP),M(G6,PQP),M(SG6,PQP),M(G6,PQP),M2(SG5,SG3,0),M2(B3,SD,PQP),M(SG6,PQP),M(SA6,PQP),M(SG6,PQP);
	M(SA5,0),M2(SD2,SD3,PQP),M(SA6,PQP),M(B6,PQP),M(SA6,PQP),M2(SD5,G3,0),M2(G,SD,PQP),M(SD6,PQP),M(E6,PQP),M(SD6,PQP),M2(SD5,SA3,0),M2(G,SD,PQP),M(SD6,PQP),M(E6,PQP),M(SD6,PQP),
	M2(E5,G2,PQP),M(E6,PQP),M(SF6,PQP),M(E6,PQP),M2(SD5,SC,0),M2(SD,SA,PQP),M(SD6,PQP),M(E6,PQP),M(SD6,PQP),M2(SC5,SA3,0),M2(SA,SD,PQP),M(SC6,PQP),M(SD6,PQP),M(SC6,PQP);
	M2(B,SG2,PQP),M(B5,PQP),M(SC6,PQP),M(B5,PQP),M(B,0),M2(SD,SG,PQP),M(B5,PQP),M(SC6,PQP),M(B5,PQP),M(SA,0),M2(B3,SD,PQP),M(SA5,PQP),M(B5,PQP),M(SA5,PQP),
	M2(SG,E2,PQP),M(SG5,PQP),M(SA5,PQP),M(SG5,PQP),M(G,0),M2(B3,D,PQP),M(G5,PQP),M(SG5,PQP),M(G5,PQP),M(SG,0),M2(SA3,D,PQP),M(SG5,PQP),M(SA5,PQP),M(SG5,PQP);
	M2(SA,SD2,PQP),M(SA5,PQP),M(B5,PQP),M(SA5,PQP),M(SD,0),M2(G3,SA3,PQP),M(SD5,PQP),M(E5,PQP),M(SD5,PQP),M(SD6,0),M2(G,SA,PQP),M(SD7,PQP),M(E7,PQP),M(SD6,PQP),
	M(SD6,0),M2(G5,SA5,PQP),M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(SD6,PQP),M(SD7,PQP),M(E7,PQP),M(SD7,PQP),M(SC6,PQP),M(SC7,PQP),M(SD7,PQP),M(SC7,PQP);
	M2(C6,SG2,PQP),M(C7,PQP),M(SC7,PQP),M(C7,PQP),M2(C6,A3,0),M2(SD,SF,PQP),M(C7,PQP),M(SC7,PQP),M(C7,PQP),M2(A5,C,0),M2(SD,SF,PQP),M(A6,PQP),M(B6,PQP),M(A6,PQP),
	M2(SG5,C3,PQP),M(SG6,PQP),M(SA6,PQP),M(SG6,PQP),M2(SG5,SG3,0),M2(SD,SF,PQP),M(SG6,PQP),M(SA6,PQP),M(SG6,PQP),M2(SF5,B3,0),M2(SD,SF,PQP),M(SF6,PQP),M(SG6,PQP),M(SF6,PQP);
	M2(E5,SC3,PQP),M(E6,PQP),M(SF6,PQP),M(E6,PQP),M(SC5,0),M2(E,A,PQP),M(SC6,PQP),M(SD6,PQP),M(SC6,PQP),M(SD5,0),M2(C,A,PQP),M(SD6,PQP),M(E6,PQP),M(SD6,PQP),
	M(E5,0),M2(SC,A,PQP),M(E6,PQP),M(SF6,PQP),M(E6,PQP),M(SD5,0),M2(SF,A,PQP),M(SD6,PQP),M(E6,PQP),M(SD6,PQP),M(SC5,0),M2(E,A,PQP),M(SC6,PQP),M(SD6,PQP),M(SC6,PQP);
	 
	M2(SD5,SD,PQP),M2(SG,B,PQP),M(SD6,PQP),M(E5,PQP),M(F5,PQP),M(SF5,PQP),M(G5,PQP),M(SG5,PQP),M(A5,PQP),M(SA5,PQP),M(B5,PQP),M(C6,PQP),M(SC6,PQP);
	M(D6,PQP),M(SD6,PQP),M(E6,PQP),M(F6,PQP),M(SF6,PQP),M(G6,PQP),M(SG6,PQP),M(A6,PQP),M(SA6,PQP),M(B6,PQP),M(C7,PQP),M(SC7,PQP);
	M2(D7,SD3,0),M2(SD,G,P/7),M(SD7,P/7),M(G7,P/7),M(E7,P/7),M(SC7,P/7),M(SA6,P/7),M(G6,P/7),
	M(D6,P/7),M(SD6,P/7),M(SF6,P/7),M(E6,P/7),M(SC6,P/7),M(SA5,P/7),M(G5,P/7),
	M(E5,PQP),M(SD5,PQP),M(SA,PQP),M(G,PQP),M(E,PQP),M(SD,PQP),M(SA3,PQP),M(SF3,PQP);
	M(SG2,PP/6),M(SD3,PP/6),M(SG3,PP/6),M(B3,PP/6),M(SD,PP/6),M(SG,PP/6),M(SD3,PP/6),M(SF3,PP/6),M(B3,PP/6),M(B5,PP/6),M(SD6,PP/6),M(B6,PP/6),
	M(SG6,PP),
	
	S(QP),M2(B,B5,0),M(SG,QP),M2(B,B5,0),M2(G,SA,QP),M2(B,B5,0),M2(SF,A,QP),M2(B,B5,0),M2(F,A,QP),M2(B,B5,0),M2(E,SG,QP);
	M2(B2,B5,QP),M2(SD,SF,QP),M2(SF3,B3,0),M2(B,SF5,QP),M2(SD,SF,QP),M2(B2,SA5,QP),M2(SD,SF,QP),
	M2(SF2,B5,QP),M2(E,SF,QP),M2(SF3,SA3,0),M2(SC5,SF5,QP),M2(E,SF,QP),M2(SF2,B5,QP),M2(E,SF,QP);
	M2(B2,SD6,QP),M2(SD,SF,QP),M2(SF3,SD5,QP),M2(B2,B5,QP),M2(SF2,SD6,QP),M2(B1,B6,QP),
	S(QP),MM(SD5,0),M(B,QP),MM(SD5,0),M2(B,D5,QP),MM(SD5,0),M2(SA,SC5,QP),MM(SD5,0),M2(A,C5,QP),MM(SD5,0),M2(SG,B,QP);
	M2(SD3,SD6,QP),M2(SF,SA,QP),M2(SA3,SD,0),M2(SD5,SA5,QP),M2(SA,SF,QP),M2(SD3,SD6,QP),M2(SA,SF,QP),
	M2(SA2,F6,QP),M2(SG,SA,QP),M2(SA3,D,0),M2(F5,SA5,QP),M2(SG,SA,QP),M2(SA2,F6,QP),M2(SG,SA,QP);
	M2(SD3,SF6,QP),M2(SA,SF,QP),M2(SA3,SF5,QP),M2(SD3,SD6,QP),M2(SA2,SF6,QP),M2(SD2,SD7,QP),
	S(QP),MM(SF5,0),M(SD5,QP),MM(SF5,0),M2(D5,F5,QP),MM(SF5,0),M2(SD,E5,QP),MM(SF5,0),M2(C5,SD5,QP),MM(SF5,0),M2(B,D5,QP);
	M2(SF3,SF6,QP),M2(SC5,SA,QP),M2(SC,SF,0),M2(SF5,SC6,QP),M2(SA,SC,QP),M2(SF3,SF6,QP),M2(SA,SC,QP),
	M2(SC3,SG6,QP),M2(B,SC5,QP),M2(SC,F,0),M2(SG5,SC6,QP),M2(B,SC5,QP),M2(SC3,SG6,QP),M2(B,SC5,QP);
	
	M2(SF3,SC6,0),M2(SF6,SA6,QP),M2(SC6,SG6,0),M(B6,QP),M2(SC,SC6,0),M2(SA6,SC7,QP),M2(SA,SC6,0),M2(SA6,SC7,QP),M2(SF5,SC6,0),M2(SG6,B6,QP),M2(SA5,SC6,0),M2(SF6,SA6,QP),
	M2(B2,B5,0),M2(SD6,SG6,QP),M2(SC6,SD6,0),M(SA6,QP),M(B3,0),M2(SD6,B6,QP),M(SG,0),M2(SD6,B6,QP),M2(SD5,SC6,0),M2(SD6,SA6,QP),M2(SG5,B5,0),M2(SD6,SG6,QP);
	M2(SC3,SA5,0),M2(SC6,SF6,QP),M2(B5,SC6,0),M(SG6,QP),M(SA3,0),M2(SC6,SA6,QP),M(SF,0),M2(SC6,SA6,QP),M2(SC5,B5,0),M2(SC6,SG6,QP),M2(SF5,SA5,0),M2(SC6,SF6,QP),
	M2(SC,SG5,0),M2(SC6,F6,QP),M2(SA5,SC6,0),M(SF6,QP),M2(F5,B5,0),M2(SC6,SG6,QP),M2(SG,B5,0),M2(SC6,SG6,QP),M2(SC,SF5,0),M2(SC6,SD6,QP),M2(B,SG6,0),M2(SC6,F6,QP),
	MM(SF5,0),M(SC6,0),M2(SF,SA,PP),MM(SF2,QP),MM(SF2,QP),MM(G2,QP),MM(G2,QP),
	
	MM(SG2,QP),MM(SG2,QP),MM(SG3,QP),MM(SG3,QP),MM(SG,QP),MM(SG,QP);
	MM(SG5,PP),M2(SD5,SG5,0),MM(SF6,QP),M(SG5,0),MM(SF6,QP),M2(SC5,SG5,0),MM(E6,QP),M(SG5,0),MM(E6,QP),
	M2(C5,SG5,0),MM(SD6,QP),M(SG5,0),MM(SD6,QP),M2(SA,SG5,0),MM(SC6,QP),M(SG5,0),MM(SC6,QP),M2(C5,SG5,0),MM(SD6,QP),M(SG5,0),MM(SD6,QP);
	M2(SC5,SG5,0),MM(E6,PP),MM(SG2,QP),MM(SG2,QP),MM(G2,QP),MM(G2,QP),
	
	MM(SF2,QP),MM(SF2,QP),MM(SF3,QP),MM(SF3,QP),MM(SF,QP),MM(SF,QP);
	MM(SF5,PP),M2(SC5,SF5,0),MM(E6,QP),M(SF5,0),MM(E6,QP),M2(B,SF5,0),MM(SD6,QP),M(SF5,0),MM(SD6,QP),
	M2(SA,SF5,0),MM(SC6,QP),M(SF5,0),MM(SC6,QP),M2(SG,SF5,0),MM(B5,QP),M(SF5,0),MM(B5,QP),M2(SA,SG5,0),MM(SC6,QP),M(SF5,0),MM(SC6,QP);
	M2(B,SF5,0),MM(SD6,PP),MM(F2,QP),MM(F2,QP),MM(E2,QP),MM(E2,QP),
	
	MM(SD2,QP),MM(SD2,QP),MM(SD3,QP),MM(SD3,QP),MM(SD,QP),MM(SD,QP);
	MM(SD5,PP),M2(SD,G,0),MM(SD5,QP),M2(SD,G,0),MM(SD5,QP),M2(F,SG,0),MM(SD5,QP),M2(F,SG,0),MM(SD5,QP),
	M2(SF,A,0),MM(E5,QP),M2(SF,A,0),MM(SD5,QP),M2(E,G,0),MM(SC5,QP),M2(E,G,0),MM(B,QP),M2(D,F,0),MM(SA,QP),M2(D,F,0),MM(SG,QP);
	M(SD,0),MM(G,PP),MM(SA1,QP),MM(SA1,QP),MM(D2,QP),MM(D2,QP),
	
	MM(SD2,QP),MM(SD2,QP),MM(SD3,QP),MM(SD3,QP),MM(SD,QP),MM(SD,QP);
	MM(SD5,PP),M2(SD5,G,0),MM(SD6,QP),M2(SD5,G,0),MM(SD6,QP),M2(F5,SG,0),MM(SD6,QP),M2(F5,SG,0),MM(SD6,QP),
	M2(SF5,A,0),MM(E6,QP),M2(SF5,A,0),MM(SD6,QP),M2(SA,G5,0),MM(SC6,QP),M2(SA,G5,0),MM(B5,QP),M2(C5,F5,0),MM(SA5,QP),M2(C5,F5,0),MM(SG5,QP);
	
	MM(G5,0),M2(SA,SD5,QP),MM(SF5,0),M2(SA,SD5,QP),MM(F5,0),M2(SG,B,QP),MM(E5,0),M2(SG,B,QP),MM(D5,0),M2(SF,A,QP),MM(SD5,0),M2(SF,A,QP),
	MM(E5,0),M2(G,SA,QP),MM(SD5,0),M2(G,SA,QP),MM(SC5,0),M2(E,G,QP),MM(B,0),M2(E,G,QP),MM(SA,0),M2(D,F,QP),MM(SG,0),M2(D,F,QP);
	MM(G,0),M2(SA3,SD,QP),MM(SF,0),M2(SA3,SD,QP),MM(F,0),M2(SG3,B3,QP),MM(E,0),M2(SG3,B3,QP),MM(D,0),M2(SF3,A3,QP),MM(SD,0),M2(SF3,A3,QP),
	MM(E,0),M2(G3,SA3,QP),MM(SD,0),M2(G3,SA3,QP),MM(SC,0),M2(E3,G3,QP),MM(B3,0),M2(E3,G3,QP),MM(SA3,0),M2(D3,F3,QP),MM(SG3,0),M2(D3,F3,QP);
	MM(G3,0),M2(SA2,SD3,QP),MM(SF3,0),M2(SA2,SD3,QP),MM(F3,0),M2(SG2,B2,QP),MM(E3,0),M2(SG2,B2,QP),MM(D3,0),M2(SF2,A2,QP),MM(SD3,0),M2(SF2,A2,QP),
	M2(E3,E,0),M2(G2,SA2,QP),M2(E3,SD,0),M2(G2,SA2,QP),M2(E3,SC,0),M2(G2,SA2,QP),M2(E3,B3,0),M2(G2,SA2,QP),M2(F3,SA3,0),M2(C2,B2,QP),M2(F3,SG3,0),M2(C2,B2,QP);
	
	M(SD2,0),M2(SA2,G3,PP),MM(D3,QP),M(D3,QP),MM(SD3,QP),M(SD3,QP),
	MM(A3,QP),M(A3,QP),MM(SA3,QP),M(SA3,QP),MM(D,QP),MM(D3,QP);
	MM(SD,QP),MM(SD3,QP),MM(A,QP),MM(A3,QP),MM(SA,QP),MM(SA3,QP),
	MM(D5,QP),MM(D,QP),MM(SD5,QP),MM(SD,QP),MM(A5,QP),MM(A,QP);
	MM(SA5,QP),MM(SA,QP),MM(D6,QP),MM(D5,QP),MM(SD6,QP),MM(SD5,QP),
	MM(D6,QP),MM(D5,QP),MM(SD6,QP),MM(SD5,QP),MM(D6,QP),MM(D5,QP);
	
	MM(SD6,QP),MM(D5,QP),MM(SD6,QP),MM(SA,QP),MM(SD6,QP),MM(G,QP),
	MM(SD6,QP),MM(SD,QP),MM(SD6,QP),MM(SC,QP),MM(SD6,QP),MM(SA3,QP);
	MM(SD6,QP),MM(G3,QP),MM(SD6,QP),MM(SD3,QP),MM(SD6,QP),MM(SC3,QP),
	MM(SD6,QP),MM(SA2,QP),MM(SD6,QP),MM(G2,QP),MM(SD6,QP),MM(SD2,QP);
	
	MM(SD6,QP),MM(SD6,QP),MM(SD6,QP),MM(SD6,QP),MM(SD6,QP),MM(SD6,QP),
	MM(SD6,QP),MM(SD6,QP),MM(SD6,QP),MM(SD6,QP),MM(SD6,QP),MM(SD6,QP);
	
	MM(SD6,QP),MM(SD6,QP),MM(SD6,QP),MM(SD6,QP),M(SD,0),MM(SD6,QP),MM(SD6,QP),
	M(SD5,0),MM(SD6,QP),MM(SD6,QP),MM(SD6,QP),MM(SD6,QP),MM(SC6,QP),MM(SC6,QP),
	MM(SG1,0),MM(B5,QP),MM(B5,QP),MM(SD3,0),M(B3,0),MM(B5,QP),MM(SD3,0),M(B3,0),MM(B5,QP),M(SG3,0),M2(B3,SD,0),MM(SA5,QP),MM(SA5,QP),
	MM(B1,0),MM(SG5,QP),MM(SG5,QP),MM(SD3,0),M(B3,0),MM(G5,QP),MM(SD3,0),M(B3,0),MM(G5,QP),M(SG3,0),M2(B3,SD,0),MM(SG5,QP),MM(SG5,QP);
	MM(SD2,0),MM(SA5,QP),MM(SA5,QP),MM(G3,0),M(SD3,0),MM(SD5,QP),MM(G3,0),M(SD3,0),MM(SD5,QP),M(SA3,0),M2(SD,G,0),MM(SD5,QP),MM(SD5,QP),
	MM(G2,0),MM(E5,QP),MM(E5,QP),M(SC,0),M2(SD,SA,0),MM(SD5,QP),M(SC,0),M2(SD,SA,0),MM(SD5,QP),M(SC,0),M2(SD,SA,0),MM(SC5,QP),MM(SC5,QP);
	MM(SG2,0),MM(B,QP),MM(B,QP),M(B3,0),M2(SD,SG,0),MM(B,QP),M(B3,0),M2(SD,SG,0),MM(B,QP),M2(B3,SD,0),MM(SA,QP),MM(SA,QP),
	M(E2,0),MM(SG,QP),MM(SG,QP),M2(SA3,D,0),MM(G,QP),M2(SA3,D,0),MM(G,QP),M2(SA3,D,0),MM(SG,QP),MM(SG,QP);
	M(SD2,0),MM(SA,QP),MM(SA,QP),M2(G3,SA3,0),MM(SD,QP),M2(G3,SA3,0),MM(SD,QP),M(G3,0),M2(SA3,SD,0),MM(SD5,QP),MM(SD5,QP),
	
	M(G,0),M2(SA,SD5,0),MM(SD6,QP),MM(SD6,QP),MM(SD6,QP),MM(SD6,QP),MM(SC6,QP),MM(SC6,QP),
	MM(G1,0),MM(C6,QP),MM(C6,QP),M(SF3,0),M2(A3,SD,0),MM(C6,QP),M(SF3,0),M2(A3,SD,0),MM(C6,QP),M(SF3,0),M2(A3,SD,0),MM(A5,QP),MM(A5,QP);
	MM(B1,0),MM(SG5,QP),MM(SG5,QP),M(SA3,0),M2(SD,A,0),MM(SG5,QP),M(SA3,0),M2(SD,A,0),MM(SG5,QP),M(SA3,0),M2(SD,A,0),MM(SF5,QP),MM(SF5,QP);
	MM(SC2,0),MM(E5,PP),MM(A3,0),M2(E3,SC,0),M2(E,SC5,QP),MM(A3,0),M2(E3,SC,0),M2(E,SC5,QP),MM(A3,0),M2(SD3,SC,0),M2(E,SD5,QP),MM(A3,0),M2(SD3,SC,0),M2(E,SD5,QP),
	MM(A3,0),M2(SC3,SC,0),M2(E,E5,QP),MM(A3,0),M2(SC3,SC,0),M2(E,E5,QP),MM(A3,0),M2(SD3,SC,0),M2(E,SD5,QP),MM(A3,0),M2(SD3,SC,0),M2(E,SD5,QP),MM(A3,0),M2(E3,SC,0),M2(E,SC5,QP),MM(A3,0),M2(E3,SC,0),M2(E,SC5,QP);
	
	MM(SD3,0),MM(SG3,0),MM(B3,0),M(SD5,QP),MM(D3,0),MM(E,QP),MM(SC3,0),MM(F,QP),MM(C3,0),MM(SF,QP),MM(B2,0),MM(G,QP),MM(SA2,0),MM(SG,QP),
	MM(A2,0),MM(A,QP),MM(SG2,0),MM(SA,QP),MM(G2,0),MM(B,QP),MM(SF2,0),MM(C5,QP),MM(F2,0),MM(SC5,QP),MM(E2,0),MM(D5,QP);
	MM(SD2,0),MM(SD5,0),M2(G2,G5,0),M2(SA2,SA5,QP), MM(D2,0),MM(E5,QP),MM(SC2,0),MM(F5,QP),MM(C2,0),MM(SF5,QP),MM(B1,0),MM(G5,QP),MM(SA1,0),MM(SG5,QP),
	MM(A1,0),MM(A5,QP),MM(SG1,0),MM(SA5,QP),MM(G1,0),MM(B5,QP),MM(SF1,0),MM(SC6,QP),MM(E1,0),MM(D6,QP);MM(SD6,QP),MM(SD1,0),
	
	MM(SG1,0),M2(B3,SD,0),M(SG,PP),MM(SD2,QP),MM(SG2,QP),MM(SD3,0),MM(B,0),M(SD5,PP),
	
	MM(SG1,0),MM(SA,0),M(SD5,QP),MM(B,QP),MM(SD2,0),MM(SC5,QP),MM(SG2,QP),MM(SD3,0),MM(B,0),M(SD5,QP),MM(SA,QP);
	MM(SG1,0),MM(B,0),M(SD5,QP),MM(SC5,QP),MM(SD2,0),MM(SD5,QP),MM(SG2,QP),MM(SD3,0),MM(SC5,QP),MM(B,QP),
	MM(SG1,0),MM(SA,0),M(SD5,QP),MM(B,QP),MM(SD2,0),MM(SC5,QP),MM(SG2,QP),MM(SD3,0),MM(B,0),M(SD5,QP),MM(SA,QP);
	MM(SG1,0),MM(B,0),M(SD5,QP),MM(SA,QP),MM(SD2,0),MM(SG,QP),MM(SG2,QP),MM(SD3,0),MM(B5,0),M(SD6,PP),
	
	MM(SG1,0),MM(SA5,0),M(SD6,QP),MM(B5,QP),MM(SD2,0),MM(SC6,QP),MM(SG2,QP),MM(SD3,0),MM(B5,0),M(SD6,QP),MM(SA5,QP);
	MM(SG1,0),MM(B5,0),M(SD6,QP),MM(SC6,QP),MM(SD2,0),MM(SD6,QP),MM(SG2,QP),MM(SD3,0),MM(SC6,QP),MM(B5,QP),
	MM(SG1,0),MM(SA5,0),M(SD6,QP),MM(B5,QP),MM(SD2,0),MM(SC6,QP),MM(SG2,QP),MM(SD3,0),MM(B5,0),M(SD6,QP),MM(SA5,QP);
	MM(SG1,0),MM(B5,0),M(SD6,QP),MM(SA5,QP),MM(SD2,0),MM(SG5,QP),MM(SG2,QP),MM(B2,0),MM(SD,0),M2(SD3,B,PP),
	
	MMM(SD3,0),MMM(SA2,QP),MMM(SD3,0),MMM(B2,QP),MMM(SD3,0),MMM(SC3,PP),MMM(SD3,0),MMM(B2,QP),MMM(SD3,0),MMM(SA2,QP);
	MMM(SD3,0),MMM(B2,QP),MMM(SD3,0),MMM(SA2,QP),MMM(SD3,0),MMM(SG2,PP),MM(SG1,0),MM(SD5,0),M2(SD2,SG5,PP),
	MMM(SD3,0),MMM(SA2,QP),MMM(SD3,0),MMM(B2,QP),MMM(SD3,0),MMM(SC3,PP),MMM(SD3,0),MMM(B2,QP),MMM(SD3,0),MMM(SA2,QP);
	MMM(SD3,0),MMM(B2,QP),MMM(SD3,0),MMM(SA2,QP),MMM(SD3,0),MMM(SG2,PP),MM(SG1,0),MM(SD5,0),M2(SD2,SG5,PP),
	MMM(SD3,0),MMM(B2,QP),MMM(SD3,0),MMM(SA2,QP),MMM(SD3,0),MMM(SG2,PP),MM(SG1,0),MM(SG5,0),M2(SD2,SD6,PP);
	MMM(SD3,0),MMM(B2,QP),MMM(SD3,0),MMM(SA2,QP),MMM(SD3,0),MMM(SG2,PP),MM(SG1,0),MM(B5,0),M2(SD2,SD6,PP),
	MMM(SD3,0),MMM(B2,QP),MMM(SD3,0),MMM(SA2,QP),MMM(SD3,0),MMM(SG2,PP),MM(SG1,0),MM(SD6,0),M2(SD2,SG6,P),
	MM(SG2,0),MM(SD6,0),M2(SD3,SG6,PP),MM(SG3,0),MM(SD6,0),M2(SD,SG6,PP),
	MM(SG,0),MM(SD6,0),M2(SD5,SG6,PP),MM(SG3,0),MM(SD6,0),M2(SD,SG6,PP),MM(SG2,0),MM(SD6,0),M2(SD3,SG6,PP);
	MM(SG1,0),MM(SD6,0),M2(SD2,SG6,PP),S(PP),S(PP),MMM(SG2,0),MM(SD3,0),M(B3,PP),S(P);
	MMM(B3,0),MMM(SG,0),M2(SD,SD6,P*3);
	Sleep(P*3);
	printf("谢谢大家！\n");
	midiOutClose(handle);
}
	return 0;	
}
