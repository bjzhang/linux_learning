//-DA=5
#if A==5
#warning A==5
//-DA=6
#elif A==6
#warning A==6
//-DA=7 -DB=0xB
#elif A==7 && B==0x0B
#warning A==7 && B==0x0B
//-DA=8 -DB=11
#elif A==8 && B==0x0B
#warning A==8 && B==11
#endif

int main(){return 0;}
