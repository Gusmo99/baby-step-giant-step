#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int remainder(int base,int power,int module) {
	unsigned long long int temp=pow(base,power);
	int temp_remainder;
	if(power==0){
		return 1;
	}
	if((int) temp==0){//if exponential to high result 0
		temp_remainder=base;
		int i;
		for(i=1;i<power;i++){
			temp_remainder=(temp_remainder*base)%module;
		}
    }else{
	    temp_remainder=temp%module;
	}
	return temp_remainder;
}


int euclide(int base,int module){//extended euclide
	int q[10],r[10],n,i;
	r[0]=base;
	q[1]=module/base;
	r[1]=module%base;
	for(i=1;r[i]!=0;i++){
		q[i+1]=r[i-1]/r[i];
		r[i+1]=r[i-1]%r[i];
	}
	n=i;
	int x[10];
	x[0]=0;
	x[1]=1;
	for(i=2;i<=n;i++){
		x[i]=-(q[i-1]*x[i-1])+x[i-2];
	}
	if(x[n]<0){
		x[n]=x[n]+module;
	}
	return x[n];
}

int main(int argc, char *argv[]) {
	int alpha,beta,module;
	printf("insert alpha: ");
	scanf("%d",&alpha);
	printf("insert beta: ");
	scanf("%d",&beta);
	printf("insert module: ");
	scanf("%d",&module);
	bool found=false;
	int N=sqrt(module-1)+1;//set initial N
    while(!found&&N>0){//until not found and still a possibility to found
    	printf("x not found, try N=%d\n",N);
	    int result[2][N];//create a matrix with the result of aj and bk
	    int i,j;
	    for(j=0;j<N;j++){
		    result[0][j]=remainder(alpha,j,module);//aj=a^j
		    int temp;
		    if(module-1-N*j>=0){
				temp=remainder(alpha,module-1-N*j,module);//calculate alpha^(p-1-nk)
	    	}else{
	    		int inverse=euclide(alpha,module);
	    		temp=remainder(inverse,-(module-1-N*j),module);
			}
			result[1][j]=remainder(beta*temp,1,module);//calculate bk=beta*(alpha^(p-1-nk))
		}
	    printf("n=%d\n",N);
	    for(i=0;i<N;i++){
	        for(j=0;j<N;j++){
	    	    if(result[0][i]==result[1][j]){//check for a couple j and k with aj=bk
	    		    found=true;
	    		    printf("found! j=%d k=%d -> x=%d\n",i,j,i+N*j);
	    		}
	        }
	    }
	    int k;
		for(k=0;k<N;k++){//print the matrix
		    printf("%d | %d | %d\n",k,result[0][k],result[1][k]);
		}
		if(!found){//reduce N to prepair to the next interaction if not found
	    	N--;
	    }
	}
	return 0;
}
