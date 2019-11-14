void get_input(x,i){
	batterytemp[i]=x;
	send(x);
}
process(){
	double sum=0;
	for(int i=0;i<batterytemp.size();i++){
		sum+=batterytemp[i];
	}
	double avg=sum/6;
	send(avg);
}

int main(){
	while(1){
		bool flag=false;
		for(int i=0;i<6;i++){
			int x=analogRead(A3);
			if(batterytemp[i]!=x){
				flag=true;
				get_input(x,i)
				
			}
		}
		if(flag){
			process();
		}
	}
}
