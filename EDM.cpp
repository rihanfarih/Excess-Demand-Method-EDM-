#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <limits.h>

const int def_size=500;
using namespace std;

struct minimax { 
    int val;
    int col;
    int row;
}; 
typedef struct minimax minimax; 

void printDebugTP(int dem[][def_size], int tp[][def_size], int d[], int s[], int tc[], int status[], int m, int n){
	for(int i=0;i<m;i++){
		string er="NS";
		for(int j=0;j<n;j++){
			cout<<tp[i][j]<<"\t("<<dem[i][j]<<")\t";
		}
		if(status[i]==1) er = "ER";
		if(status[i]==2) er = "S";
		cout<<"\t"<<s[i]<<"\t"<<er<<"\t"<<tc[i]<<"\n";
	}
	for(int i=0;i<n;i++){
		cout<<d[i]<<"\t\t";
	}
	cout<<"\n\n";
}

void initStatus(int status[], int dem[][def_size], int s[], int m, int n){
	for(int i=0;i<m;i++){
		int sum=0;
		status[i]=0;
		for(int j=0;j<n;j++){
			sum+=dem[i][j];
		}
		if(sum>s[i]) {
			status[i]=1;
		}
	}
}

void rowStatus(int status[], int dem[][def_size], int s[], int m, int n, int first, int second){
	for(int i=0;i<m;i++){
		int sum=0;
		for(int j=0;j<n;j++){
			sum+=dem[i][j];
		}
		if(sum>s[i]) {
			status[i]=1;
		}
		else if(sum<s[i]) {
			status[i]=0;
		}
		else if(sum==s[i]&&(i==first||i==second)&&status[i]!=2) {
			status[i]=2;
		}
	}
}

minimax calcDiff(int tp[][def_size], int row, minimax diff[], int m, int n, int status[]){
	int SR, i, j;
	for(int j=0; j<n;j++){
		diff[j].val = INT_MAX; //default min
		for(int i=0; i<m;  i++){
			if(row==i || status[i]==2){
				continue;
			}
			int tempDiff = tp[i][j]-tp[row][j];
			if(tempDiff<diff[j].val && tempDiff>=0){
			//cout<<"\n"<<row<<"\t"<<i<<"\t"<<tempDiff<<endl;
				diff[j].val = tempDiff;
				diff[j].row = i;
			}
			else if(tempDiff==diff[j].val && status[diff[j].row]==0){
				diff[j].row = i;
			}
		}
	}
}

int findSR(int tp[][def_size], minimax tempSR[], int row, minimax min, int m, int n, int status[]){
//Cari lokasi SR dan jumlah SR
	int ctr=0;
	for(int i=0; i<m; i++){
		if(i!=row && tp[i][min.col]-tp[row][min.col]==min.val && status[i]!=2){
			tempSR[ctr].val=tp[i][min.col];
			tempSR[ctr].row=i;
			tempSR[ctr].col=min.col;
			ctr++;
		}
	}
/*DEBUG
	for(int i=0; i<ctr; i++){
		cout<<"SRx \t"<<tempSR[i].val<<"\t"<<tempSR[i].row<<endl;
	}
	cout<<endl;
//DEBUG */
	return ctr;
}

int firstCase(int dem[][def_size], minimax min, int row, int m, int n, int d[], int s[], int tc[], minimax tempSR[], int SRctr){
	int ED=0;
	for(int j=0; j<n; j++){
		ED+=dem[row][j];
	}
	ED-=s[row];
	
	
	minimax temp;
	temp.row=tempSR[0].row;
	if(SRctr>1){
		temp.val = INT_MIN;
		for(int i=0; i<SRctr; i++){
			if(tc[i] > temp.val){
				temp.row = tempSR[i].row;
			}
		}
	}
	
	if(dem[row][min.col]>=ED){
		dem[row][min.col]-=ED;
		dem[temp.row][min.col]+=ED;
	}
	else{
		dem[temp.row][min.col]+=dem[row][min.col];
		dem[row][min.col]=0;
	}
	return temp.row;
}

int excessDemand(int tp[][def_size], int row, minimax min, minimax diff[], int m, int n, int dem[][def_size], int s[], int d[], int tc[], int status[], minimax tempSR[], int SRctr){
	//HITUNG EXCESS DEMAND
		int ED=0;
		for(int j=0; j<n; j++){
			ED+=dem[row][j];
		}
		ED-=s[row];
		
	//
	//Rute B
	if(ED>=dem[row][min.col]){
		int temp;
		int itr=0;
		if(SRctr>1){
			temp=tc[tempSR[0].row];
			for(int i=1; i<SRctr; i++){
				if(temp<tc[tempSR[i].row]){
					temp = tc[tempSR[itr].row];
					itr+=1;
				}
			}
		}
		int tempFlag=-1;
		if(status[tempSR[itr].row]==1){
			for(int j=0; j<n; j++){
				// kalau nilai diffnya sama, kolomnya berbeda, dan statusnya tidak ER, pilih
				if(diff[min.col].val == diff[j].val && j!= min.col && status[diff[j].row]!=1){
					tempFlag=j;
					break;
				}
			}
		}
		//
		int a=tempSR[itr].row;
		if(tempFlag!=-1) {
			min.col=tempFlag;
			a=diff[tempFlag].row;
		}
		int TA=0;
		for(int j=0; j<n; j++){
			TA+=dem[a][j]; //total alokasi SR
		}
		if(dem[row][min.col] <= s[a]-TA){
			dem[a][min.col]+=dem[row][min.col];
			dem[row][min.col]=0;
		}
		else if((dem[row][min.col] > s[a]-TA) && s[a]-TA>0){
			dem[a][min.col]+=s[a]-TA;
			dem[row][min.col]-=s[a]-TA;
			//satisfy second
		}
		else{
			dem[a][min.col]+=dem[row][min.col];
			dem[row][min.col]=0;
		}
		return a;
	}
	// Rute A
	else if(ED<dem[row][min.col]){
		minimax temp;
		temp.row=tempSR[0].row;
		if(SRctr>1){
			temp.val = INT_MIN;
			for(int i=0; i<SRctr; i++){
				if(tc[i] > temp.val){
					temp.row = tempSR[i].row;
				}
			}
		}
		
		if(dem[row][min.col]>=ED){
			dem[row][min.col]-=ED;
			dem[temp.row][min.col]+=ED;
		}
		else{
			dem[row][min.col]=0;
			dem[temp.row][min.col]+=dem[row][min.col];
		}
		
		return temp.row;
	}
}

int main(){
	int deb;
	int m, n, i, j; //ukuran matrix TP
	
	string NamaFile = "C01.txt"; //init nama file
	
	ifstream inFile;
	inFile.open(NamaFile.c_str());
	if (!inFile) {
	    cout << "Unable to open file";
	    exit(1); // terminate with error
	}
	
	inFile>>m;
	inFile>>n;
	
	int tp[def_size][def_size]; int d[n], s[m], tc[m], ts, td; //init matrix
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			inFile>>tp[i][j]; //input TP
		}
	}
	ts=0;
	for(j=0;j<m;j++){
		inFile>>s[j];
		ts+=s[j];
	}
	td=0;
	for(i=0;i<n;i++){
		inFile>>d[i];
		td+=d[i];
	}

// HITUNG TOTAL COST 
	for(i=0;i<m;i++){  
		tc[i]=0;
		for(j=0;j<n;j++){
			tc[i]+=tp[i][j]; //assign TC
		}
	}
/* PRINT TOTAL COST
    cout<<"\nTC : ";
	for(i=0; i<n;i++){
		cout<<tc[i]<<" ";
	}
*/
// PRINT TP INITIAL
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			cout<<tp[i][j]<<"\t";
		}
		cout<<"\t"<<s[i]<<"\t"<<tc[i]<<"\n";
	}
	
	for(i=0;i<n;i++){
		cout<<d[i]<<"\t";
	}
	cout<<"\n\n";
//
// ALOKASI DEMAND
	minimax min;	
	int dem[def_size][def_size]; //init demand
	for(j=0;j<n;j++){  
		//default = baris 1	
		min.val=tp[0][j];
		min.col=j;
		min.row=0;
		dem[0][j]=d[j];
		//default = baris 1
		for(i=1;i<m;i++){ //kolom*baris
			if(tp[i][j]<=min.val){
				if(tp[i][j]==min.val && tc[i]<tc[min.row]){
					dem[i][j]=0;
					continue;
				}
				dem[i][j]=d[j];
				dem[min.row][j]=0;
				min.row=i;
				min.val=tp[i][j];
			}
		}
	}

/* PRINT DEMAND
    cout<<"\nDemand\n";
	for(i=0;i<m;i++){
			for(j=0;j<n;j++){
				cout<<dem[i][j]<<"\t";
			}
			cout<<"\n";
		}
*/	
	int status[m]; //init status Excess row
	initStatus(status, dem, s, m, n);
	//0 NS, 1 ER

//PRINT ITERASI
	printDebugTP(dem, tp, d, s, tc, status, m, n);
//
/*PRINT SELECTED ER
	cout<<"\nEXCESS ROW DIHITUNG : "<<row+1<<"\n";
// */

//set k to n for n itteration
int k=100;
//

while(k){
//Dummy data 
k--;
//
//ER Check=
	int row=0;
	int ERctr=0;
	for(i=0;i<m;i++){
		if(status[i]==1){
			if(ERctr==0) row=i;
			ERctr+=1;
		}
	}
	for(i=0;i<m;i++){
		if(status[i]==1){
			if(ERctr>1 && tc[i] < tc[row]){
				row=i;
//cout<<"\ROW\t\t: "<<row<<endl;//debug
				continue;
			}
			else if(ERctr==1){
				row=i;
				continue;
			}
//			cout<<"\n"<<i<<"  "<<row<<endl;
		}
	}
//

//HITUNG DIFF
	minimax diff[def_size];
	calcDiff(tp, row, diff, m, n, status);
	min.val = INT_MAX;
	int diffCTR = 0;
	for(j=0;j<n;j++){
		//least Demand
		if(dem[row][j]==0) continue;
		
		if(diff[j].val==min.val){
			diffCTR++;
			if (d[j] < d[min.col]) min.col=j;
		}
		
		if(diff[j].val<min.val){
			min.val=diff[j].val;
			min.col=j;
			diffCTR=1;
		}
	}
/*
//PRINT DIFF
    cout<<"\nDiff\t\t: ";
	for(j=0;j<n;j++){
		cout<<diff[j].val<<"\t";
	}
	cout<<"\nRow x Column\t: "<<diff[min.col].row+1<<" ||  "<<min.col+1<<"\n"; //debug lokasi diff
*/
//SR PROCESSING
	minimax tempSR[def_size];
	int SRctr=0;
	SRctr=findSR(tp, tempSR, row, min, m, n, status); //FIND SR
//SR PROCESSING
// ,tempSR,SRctr
//DIFF>1 :
	int first=row;
	int second;
	if(diffCTR>1){
		second = excessDemand(tp, row, min, diff,  m, n, dem, s, d, tc, status, tempSR, SRctr );
//
	}
//DIFF == 1;
	else{
		if(ts==td){
			if(s[row]!=s[diff[min.col].row]){
				second = excessDemand(tp, row, min, diff,  m, n, dem, s, d, tc, status, tempSR, SRctr);
			}
			else{
				second = firstCase(dem, min, row, m, n, d, s, tc, tempSR, SRctr);
			}
		}
		else{
			second = excessDemand(tp, row, min, diff,  m, n, dem, s, d, tc, status, tempSR, SRctr);
		}
	}	
	
	// FINISH CODE
//	cout<<"FIRST\t"<<first<<" SECOND\t"<<second<<endl; //debug row first dan row second

	rowStatus(status, dem, s, m, n, row, second);
	printDebugTP(dem, tp, d, s, tc, status, m, n);
		//0 NS, 1 ER, 2S
		int doneFlag = 1;
			for(i=0; i<m; i++){
				if(status[i]==1){
					doneFlag = 0;
					break;
				}
			}
		if(doneFlag == 1){
			int total=0;
			for(j=0;j<n;j++){
				for(i=0;i<m;i++){
					if(dem[i][j]==0) continue;
					total+= (tp[i][j]*dem[i][j]);
				}
			}
			cout<<"\nTotal : "<<total<<"\nFinished"<<endl;
			return 0;
		}
	// FINISH CODE
	
}
	return 0;
}
