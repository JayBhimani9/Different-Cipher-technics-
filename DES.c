#include<stdio.h>
#include<string.h>
#include<ctype.h>

int sbox[4][16]={{14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
                 {0,15,7,4,14,2,13,10,3,6,12,11,9,5,3,8},
                 {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
                 {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}};
int binarymap[16][4]={{0,0,0,0}, {0,0,0,1}, {0,0,1,0}, {0,0,1,1},
                      {0,1,0,0}, {0,1,0,1}, {0,1,1,0}, {0,1,1,1},
                      {1,0,0,0}, {1,0,0,1}, {1,0,1,0}, {1,0,1,1},
                      {1,1,0,0}, {1,1,0,1}, {1,1,1,0}, {1,1,1,1}};
int binarytoDecimal(int n) {
  int num = n;
  int dec_value = 0;
  int base = 1;
  int temp = num;
  int last_digit;
  while (temp) {
    last_digit = temp % 10;
    temp = temp / 10;
    dec_value += last_digit * base;
    base = base * 2;
  }
  return dec_value;
}
void Initial_permutation(int *old,int *new){
    int map[8]={4,0,5,1,6,2,7,3};
    for (int i=0;i<8;i++){
        for (int j=0;j<8;j++){
            *(new+((8*map[j])+(7-i))) = *(old+(8*i+j));
        }
    }
}
void Expand_permutation(int *old,int *new){
    for (int i = 0; i < 8; i++)
    {
        for (int j = 1; j < 5; j++)
        {
            *(new+(6*i+j))=*(old+(4*i+(j-1)));
        }
    }
    *new=*(old+(4*7+3));
    for (int i = 1; i < 8; i++)
    {
        *(new+i*6)=*(old+(i*4-1));
        *(new+(i*6-1))=*(old+(i*4));
    }
    *(new+(6*7+5))=*(old);
}
void left_shift_circular(int *data){
    int a=*data;
    int b=*(data+28);
    for(int i=0;i<27;i++){
        *(data+i)=*(data+i+1);
        *(data+i+28)=*(data+i+29);
    }
    *(data+27)=a;
    *(data+55)=b;
}
void inverse_initial_permutation(int *old, int *new) {
  int odd = 1;
  int even = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (i < 4)
        *(new + (8 * (7 - j) + odd)) = *(old + (i * 8 + j));
      else
        *(new + (8 * (7 - j) + even)) = *(old + (i * 8 + j));
    }
    if (i < 4)
      odd += 2;
    else
      even += 2;
  }
}
void keyfill(int *rk, int *sk){
    int n=0;
    for(int i=0;i<8;i++){
        for(int j=0;j<6;j++){
            *(rk+(6*i+j))=*(sk+n);
            n++;
        }
    }
}
void DES(FILE *p,char *key){
    int data[8][8];
    int initial_data[8][8];
    int *d = &data[0][0];
    int *id = &initial_data[0][0];
    int num;
    int left[8][4];
    int right[8][4];
    int temp[8][4];
    int expand[8][6];
    int xor_result[8][6];
    int *ex_id = &expand[0][0];
    int *ri_id = &right[0][0];
    int *temp_id = &temp[0][0];
    int key_data[7][8];
    int klen = strlen(key);
    int roundkey[8][6];
    int *rk_id=&roundkey[0][0];
    int s_box_res[8][4];
    int row=0,col=0;
    FILE *fp=fopen("CIPHER.txt","w");
    for(int i=0;i<klen ; i++){
        num=*(key+i);
        for(int j=7;j>=0;j--){
            key_data[i][j] = num % 2;
            num = num / 2;
        }
    }
    int shiftkey_data[2][28];
    int *key_id=&shiftkey_data[0][0];
    int c=0;
    
    char a=getc(p);
    while (a!=EOF)
    {
        for(int i=0;i<8;i++){
            num=a;
            if (a!=EOF)
                for(int j=7;j>=0;j--){
                    data[i][j] = num % 2;
                    num = num / 2;
                }
            else{
                num=0;
                for(int j=7;j>=0;j--){
                    data[i][j] = num % 2;
                    num = num / 2;
                }
            }
            a=getc(p);
        }
        printf("Data:\n");
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++)
                printf("%d ",data[i][j]);
            printf("\n");
        }
        Initial_permutation(d,id);
        printf("\nInitial permutation Data:\n");
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++)
                printf("%d ",initial_data[i][j]);
            printf("\n");
        }
        for(int i=0;i<8;i++){
            for(int j=4;j<8;j++){
                right[i][j-4]=initial_data[i][j];
            }
            for (int k = 0; k < 4; k++)
            {
                left[i][k]=initial_data[i][k];
            }
        }
        c=0;
        for (int i = 0; i < 3; i++)
        {
            for(int j=0;j<8;j++){
                shiftkey_data[0][c]=key_data[i][j];
                c++;
            }
        }
        for(int j=0;j<4;j++){
            shiftkey_data[0][c]=key_data[3][j];
            c++;
        }
        c=0;
        for(int j=4;j<8;j++){
            shiftkey_data[1][c]=key_data[3][j];
            c++;
        }
        for (int i = 4; i < 7; i++)
        {
            for(int j=0;j<8;j++){
                shiftkey_data[1][c]=key_data[i][j];
                c++;
            }
        }
        printf("original key-shift\n");
        for(int i=0;i<2;i++){
            for(int j=0;j<28;j++){
                printf("%d ",shiftkey_data[i][j]);
            }
            printf("\n");
        }
        for (int r=0;r<16;r++){
            printf("Round %d\n",r+1);
            printf("Left: \n");
            for(int i=0;i<8;i++){
                for(int j=0;j<4;j++){
                    printf("%d ",left[i][j]);
                }
                printf("\n");
            }
            printf("Right: \n");
            for(int i=0;i<8;i++){
                for(int j=0;j<4;j++){
                    printf("%d ",right[i][j]);
                }
                printf("\n");
            }
            left_shift_circular(key_id);
            keyfill(rk_id,key_id);
            printf("Round key\n");
            for (int i = 0; i < 8; i++)
            {
                for(int j=0;j<6;j++){
                    printf("%d ",roundkey[i][j]);
                }
                printf("\n");
            }
            
            // printf("\nRight Data:\n");
            // for(int i=0;i<8;i++){
            //     for(int j=0;j<4;j++)
            //         printf("%d ",right[i][j]);
            //     printf("\n");
            // }
            Expand_permutation(ri_id,ex_id);
            // printf("\nExpanded Data:\n");
            // for(int i=0;i<8;i++){
            //     for(int j=0;j<6;j++)
            //         printf("%d ",expand[i][j]);
            //     printf("\n");
            // }
            //printf("Xor result of expanded right with key\n");
            for(int i=0;i<8;i++){
                for(int j=0;j<6;j++){
                    xor_result[i][j]=(expand[i][j]+roundkey[i][j])%2;
                    printf("%d ",xor_result[i][j]);
                }
                printf("\n");
            }
            printf("result of S-box\n");
            for(int i=0;i<8;i++){
                row=binarytoDecimal(((10*xor_result[i][0])+xor_result[i][5]));
                col=binarytoDecimal(((1000*xor_result[i][1])+(100*xor_result[i][2])+(10*xor_result[i][3])+xor_result[i][4]));
                for(int j=0;j<4;j++){
                    s_box_res[i][j]=binarymap[sbox[row][col]][j];
                    printf("%d ",s_box_res[i][j]);
                }
                printf("\n");
            }
            // P-Permutaion
            temp[0][0]=s_box_res[3][3];temp[0][1]=s_box_res[0][0];temp[0][2]=s_box_res[0][1];temp[0][3]=s_box_res[4][2];
            temp[1][0]=s_box_res[1][2];temp[1][1]=s_box_res[3][2];temp[1][2]=s_box_res[1][3];temp[1][3]=s_box_res[3][0];
            temp[2][0]=s_box_res[4][3];temp[2][1]=s_box_res[5][2];temp[2][2]=s_box_res[5][3];temp[2][3]=s_box_res[7][1];
            temp[3][0]=s_box_res[5][0];temp[3][1]=s_box_res[6][1];temp[3][2]=s_box_res[3][1];temp[3][3]=s_box_res[1][1];
            temp[4][0]=s_box_res[7][0];temp[4][1]=s_box_res[1][0];temp[4][2]=s_box_res[7][7];temp[4][3]=s_box_res[5][1];
            temp[5][0]=s_box_res[2][3];temp[5][1]=s_box_res[4][1];temp[5][2]=s_box_res[6][2];temp[5][3]=s_box_res[2][2];
            temp[6][0]=s_box_res[6][3];temp[6][1]=s_box_res[7][2];temp[6][2]=s_box_res[0][2];temp[6][3]=s_box_res[0][3];
            temp[7][0]=s_box_res[4][0];temp[7][1]=s_box_res[2][1];temp[7][2]=s_box_res[2][0];temp[7][3]=s_box_res[6][0];
            printf("Result after P-box\n");
            for(int i=0;i<8;i++){
                for(int j=0;j<4;j++){
                    printf("%d ",temp[i][j]);
                    temp[i][j]=(left[i][j]+temp[i][j])%2;
                }
                printf("\n");
            }
            for(int i=0;i<8;i++){
                for(int j=0;j<4;j++){
                    left[i][j]=right[i][j];
                    right[i][j]=temp[i][j];
                }
            }
        }
        for(int i=0;i<8;i++){
            for(int j=4;j<8;j++){
                data[i][j]=left[i][j-4];
            }
            for (int k = 0; k < 4; k++)
            {
                data[i][k]=right[i][k];
            }
        }
        // printf("Result after allround and sweap\n");
        // for(int i=0;i<8;i++){
        //     for(int j=0;j<8;j++){
        //         printf("%d ",data[i][j]);
        //     }
        //     printf("\n");
        // }
        inverse_initial_permutation(d,id);
        printf("Final Answer: \n");
        for (int i = 0; i < 8; i++)
        {
            for(int j=0;j<8;j++){
                printf("%d ",initial_data[i][j]);
                fprintf(fp,"%c",initial_data[i][j]+'0');
            }
            printf("\n");
        }
    }
    fclose(fp);
}

int main(int argc, char const *argv[])
{
    FILE *fp;
    char key[8]={'1','1','0','0','0','0','0','0'};
    char *k = &key[0];
    fp = fopen("plantext.txt", "r");
    printf("Enter 7 character key: ");
    scanf("%s",key);
    printf("%s\n",key);
    DES(fp,k);
    fclose(fp);
    printf("Check CIPHER file\n");
    return 0;
}
