/*
 * led-matrix-4.c
 *
 * Created: 05-09-2020 18:35:07
 * Author : user
 */ 









#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>



static int lt=0; static int rt=0; static int up=0; static int dn=0;
static int j,j1,j2,j3;
static int ex=0;
 static int zd[100];
static int zc[100];
static int zr[100];
 static int zl[100];
static int zx=0;
static int zy=0;
static int za=1;
static int new=0;
static int f9,f8,f7,f6;
static int length_snake=4;
static int fx=0;
void food(){
	
	if(new==0){
		
			f9=rand()%8;
			f8=rand()%8;
			f7=(int)(pow(2,f9)+0.5);
			f6=(int)(pow(2,f8)+0.5);
			if(bit_is_clear(PINB,f9)&& bit_is_set(PIND,f8)){
				PORTB =f7;
				PORTD = ~f6;
				new=1;
			return 0;
			}
			else{
				food();
			}
		
	}

	
	
	_delay_ms(90);
	
	
}










void dirr (int l,int r1,int r2 )	{
	PORTD = 0b11111111;
	PORTB =(int)(pow(2,(r1-1))+0.5);
	int f=l;
	
	int m=0;
	j=r2;
	int d;
	for( d=0;d<f;d++){
		m=m+(int)(pow(2,j)+0.5);
		j--;
		if(j<0){
			j=7;
		}
	}
	PORTD  &= ~(m);
	if(PORTB==f7 && f8==j){
		new=0;
		food();
		fx=1;
	}

	_delay_ms(35);
	
}



void dirl (int l,int r1,int r2 )	{
	PORTD = 0b11111111;
	PORTB =(int)(pow(2,(r1-1))+0.5);
	int f=l;
	
	int m=0;
	j1=r2;
	int d;
	for( d=0;d<f;d++){
		m=m+(int)(pow(2,j1)+0.5);
		j1++;
		if(j1>7){
			j1=0;
		}
	}
	PORTD  &= ~(m);
	if(PORTB==f7 && f8==j1){
		new=0;
		food();
		fx=1;
	}

	_delay_ms(35);
	
}






void dird(int l,int c1,int c2){
	
	PORTB =0b00000000;
	
	PORTD = ~((int)(pow(2,(7-c1))+0.5));
	int m1=0;
	 j2=c2;
	for(int d1=0;d1<l;d1++){
		m1=m1+(int)(pow(2,j2)+0.5);
		j2++;
		if(j2>7){
			j2=0;
		}
	}
	
	PORTB |= m1;
	if(PORTD== ~f6 && j2==f9){
		new=0;
		food();
		fx=0;
	}
	
	_delay_ms(35);
	
}




void diru(int l,int c1,int c2){
	PORTD = 0b11111111;
	PORTB =0b00000000;
	PORTD = ~((int)(pow(2,(7-c1))+0.5));
	int m1=0;
	 j3=c2;
	for(int d1=0;d1<l;d1++){
		m1=m1+(int)(pow(2,j3)+0.5);
		j3--;
		if(j3<0){
			j3=7;
		}
	}
	PORTB |= m1;
	if(PORTD== ~f6 && j3==f9){
		new=0;
		food();
		fx=0;
	}
	
	
	
	_delay_ms(35);
}

void cond(){
	if(bit_is_clear(PINA,5)){
		ex=lt=1;
		rt=up=dn=0;
	}
	_delay_ms(50);
	if(bit_is_clear(PINA,3)){
		ex=rt=1;
		lt=up=dn=0;
	}
	_delay_ms(50);
	if(bit_is_clear(PINA,0)){
		ex=up=1;
		rt=lt=dn=0;
	}
	_delay_ms(50);
	if(bit_is_clear(PINA,7)){
		ex=dn=1;
		rt=up=lt=0;
	}
	_delay_ms(50);
}




int main(void)
{
	DDRB = 0xff;
	DDRD = 0xff;
	DDRA = 0x00;
	//	PORTB =0b00000001;   code for lighting top left led
	//	PORTD = 0b01111111;
	PORTA = 0b11111111;
	
	PORTD = 0b11111111;
	PORTB =0b00000001;
	int h=7;
	int lm=224;
	int v=0;
	int h2=0;
	int v1=7;
	
	int l1,l2,l3,l4;
	l3=l4=l1=l2=1;
	 int column;
	int row;
	
	while (1)
	{
		
		if(bit_is_clear(PINA,1)){
			
			if(ex==0){
			   zd[zx]=3;
			 
			   
				 row =3;
			
			l1=length_snake;
			  zl[zx]=l1;
			if(ex==0){
				dirr (l1,row,h );
		
				h--;
				
				if(h<0){
					h=7;
				}
				zc[zx]=h;
				zr[zx]=row;
				
				_delay_ms(500);
			}
			}
		
		
		cond();	
		food();

		if(rt==1 && ex!=0  ){
		
		
			if(l1==1 && l2>1){
				l2=1;
				zx++;
				row=j2;
				if(row<=0){
					row=8;
				}
				h=7-column;
			}
			if(l1==1 && l4>1){
				l4=1;
				zx++;
				h=7-column;
				row=j3+2;
				if(row>8){
					row=1;
				}
			}
	
			if(l1!=length_snake){
				l1++;
			}
						dirr (l1,row,h );
						if(l1==length_snake){
							h--;
						}
						if(h<0){
							h=7;
						}
						
			_delay_ms(500);
	               zd[zx]=3;
	               zl[zx]=l1;
	               zc[zx]=h;
	               zr[zx]=row;
				   
				   if(fx==1){
					   fx=0;
					   length_snake++;
					   zl[zy]++;
				   }
				 
				
		}
		
		
		cond();
	if(new==1){
		PORTB =f7;
		PORTD = ~f6;
		_delay_ms(20);
	}
		
		if(dn==1 ){
		
			
			if(l2==1 && l1>1){
				l1=1;
                  zx++;
		       v=row-1;
				column=7-j-1;
				if(column < 0){
					column=7;
				}
			
				}
		   
		  
			if(l2==1 && l3>1){
				l3=1;
				zx++;
				v=row-1;
				column=7-j1+1;
				if(column >7){
					column = 0;
				}
	
				}
			if(l2!=length_snake){
				l2++;
			}
			
			

			
			dird(l2,column,v);
			//	_delay_ms(250);
			if(l2==length_snake){
				v++;
			}
			
			if(v>7){
				v=0;
			}
				_delay_ms(500);
			  zd[zx]=2;
			  zl[zx]=l2;
			zc[zx]=v;
			zr[zx]=column; 
			  if(fx==1){
				  fx=0;
				  length_snake++;
				  zl[zy]++;
			  }
			
		}
		
		
		
			cond();
		if(new==1){
			PORTB =f7;
			PORTD = ~f6;
			_delay_ms(20);
		}	
	
		if(lt==1){
			
				if(l3==1 && l4>1){
					l4=1;
					zx++;
					h2=7-column;
					row=(j3+2);
					if(row>8){
						row=1;
					}
				}
				if(l3==1 && l2>1){
					l2=1;
					zx++;
					row=j2;
					if(row<=0){
						row=8;
					}
					h2=7-column;
				}
				if(l3!=length_snake){
					l3++;
				}
				
				dirl (l3,row,h2 );
				if(l3==length_snake){
					h2++;
				}
				if(h2>7){
					h2=0;
				}
				
				
					_delay_ms(500);
			  zd[zx]=4;
			  zl[zx]=l3;
			  zc[zx]=h2;
			  zr[zx]=row;
			   if(fx==1){
				   fx=0;
				   length_snake++;
				   zl[zy]++;
			   }
	
			
		}
		
		
			cond();
			if(new==1){
				PORTB =f7;
				PORTD = ~f6;
				_delay_ms(20);
			}
		
		
		if(up==1){
			
		
	
		if(l4==1 && l1>1){
			l1=1;
			zx++;
			v1=row-1;
			column=7-j-1;
			if(column < 0){
				column=7;
			}
			
		}
		
		if(l4==1 && l3>1){
			l3=1;
			zx++;
			v1=row-1;
			column=7-j1+1;
			if(column >7){
				column = 0;
			}
			
		}
		if(l4!=length_snake){
		l4++;
	}
	diru(l4,column,v1);
	if(l4==length_snake){
		v1--;
	}
	if(v1<0){
		v1=7;
	}
		_delay_ms(500);
	  zd[zx]=1;
	  zl[zx]=l4;
	  zc[zx]=v1;
	  zr[zx]=column;
	   if(fx==1){
		   fx=0;
		   length_snake++;
		   zl[zy]++;
	   }
	   

	 
	
}
		
		
		
		
		
		
		
		
		if(new==1){
			PORTB =f7;
			PORTD = ~f6;
			_delay_ms(20);
		}
		
		
		
		
           	cond();
		
		
		
		
				if( zy<zx){
					
					
					
					
					
					if(zd[zy]==3 && zl[zy]>1){
					
					zl[zy]--;
					
					dirr (zl[zy],zr[zy],zc[zy]);
					zc[zy]--;
					if(zc[zy]<0){
						zc[zy]=7;
					}
						
						
				}
				if(zd[zy]==4 && zl[zy]>1){
					
					zl[zy]--;
					
					dirl (zl[zy],zr[zy],zc[zy] );
					zc[zy]++;
					if(zc[zy]>7){
						zc[zy]=0;
					}
					
						
				}
				if(zd[zy]==1 && zl[zy]>1){
					
					zl[zy]--;
					
					diru (zl[zy],zr[zy],zc[zy] );
					zc[zy]--;
					if(zc[zy]<0){
						zc[zy]=7;
					}
					
						
				}
				if(zd[zy]==2 && zl[zy]>1){
					
					zl[zy]--;
					
					dird (zl[zy],zr[zy],zc[zy] );
					zc[zy]++;
					if(zc[zy]>7){
						zc[zy]=0;
					}
						
						
				}
				_delay_ms(500);
				if(zl[zy]==1){
					
					zy++;
				}
				for(int kl=(zy+1);kl<zx;kl++){
					if(zd[kl]==1 && zl[kl]>1){
						diru (zl[kl],zr[kl],zc[kl] );
					}
					if(zd[kl]==2 && zl[kl]>1){
						dird (zl[kl],zr[kl],zc[kl] );
					}
					if(zd[kl]==3 && zl[kl]>1){
						dirr (zl[kl],zr[kl],zc[kl] );
					}
					if(zd[kl]==4 && zl[kl]>1){
						dirl (zl[kl],zr[kl],zc[kl] );
					}
				}
			
				}
				
						
				
				
			
	
				
		
	
			
			
			
			
			
			
			
		
				
			
		
		
		



		}
		
		
	}

}




























