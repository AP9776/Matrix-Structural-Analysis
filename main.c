#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int projectrepeat=1;
    while(projectrepeat==1){
    ///start of the project

    int i,j,counter;



    ///section 1 : Inputs ------------------------------------------------------------------------------------------------------
    printf("\n\n\n section 1 : Inputs ------------------------------------------------------------------------------------------------------\n\n\n");


    ///structure type
    int strtype;
    printf("please enter the type of structural elements : \n 1-truss \n 2-Beam \n 3-column \n 4-mixture of the above \n");
    scanf("%d",&strtype);



    ///input number of materials
    int material;
    printf("please enter the number of materials ; \n");
    scanf("%d",&material);

    ///material input
    float E[20];
    i=0;
    while(i<material){
        printf("please enter the elastic modulus of material %d : \n",i+1);
        scanf("%f",&E[i]);
        i++;
    }

    ///input number of materials
    int inertia=0;
    float I[20];

    if(strtype>1){
            printf("please enter the number of (moment of inertia)s ; \n");
            scanf("%d",&inertia);

            i=0;
            while(i<inertia){
                    printf("please enter the moment of inertia %d : \n",i+1);
                    scanf("%f",&I[i]);
                    i++;
            }
    }


    ///input number of Cross sectional Areas
    int area=0;
    if(strtype!=2){
            printf("please enter the number of cross sectional Areas ; \n");
            scanf("%d",&area);
    }

    //Area input//
    float A[20];
    if(strtype!=2){
                i=0;
                while(i<area){
                        printf("please enter the cross sectional Area %d : \n",i+1);
                        scanf("%f",&A[i]);
                        i++;
                }
    }


     ///structure information based on inputs
     printf("\n\n\n");

     printf("\n Elasticity matrix: \n");
     i=0;
     while(i<material){
            printf("E%d=%f\n",i+1,E[i]);
            i++;
     }

     if(strtype>1){
            // I matrix//
                printf("\n I matrix: \n");
                i=0;
                while(i<inertia){
                        printf("I%d=%f \n",i+1,I[i]);
                        i++;
                }
     }

    ///A matrix
     if(strtype!=2){
             printf("\n Area matrix: \n");
             i=0;
             while(i<area){
                    printf("A%d=%f \n",i+1,A[i]);
                    i++;
             }
     }
     printf("\n\n\n");






     ///section 2 : Joints ----------------------------------------------------------------------------------------------------
     printf("\n\n\n section 2 : Joints ----------------------------------------------------------------------------------------------------\n\n\n");





    ///input number of joints
    int JN;
    printf("please enter the number of joints; ( at least 2) \n");
    JN=1;
    while(JN<2){
        scanf("%d",&JN);
        if(JN<2){
            printf("The number of joints is not enough : \n");
        }
    }

    ///creation of joint structure
    struct joint{
        float coord[2],p[3];
        int DOF[3],num,ELN[20];
    }n[JN];



    ///input joint coordinates and DOFs

    i=0;
    while(i<JN){
        n[i].num=i+1;
        printf("please enter the coordinates of joint %d (x,y): \n",n[i].num);
        scanf("%f",&n[i].coord[0]);
        scanf("%f",&n[i].coord[1]);
        i++;
    }

    int NDOF=0;
    i=0;
    while(i<JN){
        printf("please enter the DOFs of joint %d in this order : Horizontal , Vertical , rotational \n",n[i].num);
        scanf("%d%d%d",&n[i].DOF[0],&n[i].DOF[1],&n[i].DOF[2]);
        for(j=0;j<=2;j++){
            if(n[i].DOF[j]!=0){
                    NDOF++;
            }
        }
        i++;
    }


    /* input joint DOFs
    int NDOF=0;
    i=0;
    while(i<JN){
        printf("please enter the number of the joint (from 1 to %d): \n",JN);
        scanf("%d",&jointnum);
        printf("please enter the DOFs of joint %d in this order : Horizontal , Vertical , rotational 1\n",jointnum);
        for(j=0;j<=2;j++){
            scanf("%d",&n[jointnum].DOF[j]);
            if(n[i].DOF[j]!=0){
                NDOF++;
            }
        }
    i++;
    } */

    ///numbering DOFs in restrained and non-restrained order
    int resDOFM[NDOF][3];
    int DOFM[NDOF][3];
    i=0;
    counter=1;

    while(i<JN){
        for(j=0;j<=2;j++){
            resDOFM[i][j]=n[i].DOF[j];
            DOFM[i][j]=counter;
            counter++;
        }
    i++;
    }

    ///joint and DOF information

    printf("\n The structure has %d Joints \n",JN);
    printf("The structure has %d Degrees of freedom \n \n",NDOF);

    i=0;
    printf("joint coordinations matrix (x,y): \n");
    while(i<JN){
        printf("joint %d: \t \t",n[i].num);
        printf("%f \t",n[i].coord[0]);
        printf("%f \t",n[i].coord[1]);
        printf("\n");
        i++;
    }

    printf("\n DOFs Matrix ( restrained order ); \n");
    i=0;
    while(i<JN){
        for(j=0;j<=2;j++){
            printf("%d \t",resDOFM[i][j]);
        }
        printf("\n");
    i++;
    }

    //printf("\n DOFs Matrix ( non-restrained order ); \n");

    //int DOFM[NDOF][3];
    //i=0;
    //counter=1;
    //while(i<JN){
        //for(j=0;j<=2;j++){
            //DOFM[i][j]=counter;
            //printf("%d \t",DOFM[i][j]);
            //counter++;
        //}
        //printf("\n");
    //i++;
    //}


    printf("\n DOFs Matrix ( non-restrained order ); \n");
    i=0;
    while(i<JN){
        for(j=0;j<=2;j++){
            printf("%d \t",DOFM[i][j]);
        }
        printf("\n");
    i++;
    }







    ///section 3 : Elements-------------------------------------------------------------------------------------------------
    printf("\n\n\n section 3 : Elements-------------------------------------------------------------------------------------------------\n\n\n");


    ///input number of elements
    int ELN;
    printf("please enter the number of elements: ( at least %d) \n");
    scanf("%d",&ELN);

    ///creation of element structure
    struct element{
        int type,JN[2],num,DOF[2][3],dof[6];
        float E,I,A,L,C,S;
        float coord[2][2],k[6][6],alpha[6][6],k0[6][6],r0[6][6],r[6][6],d0[6][6],d[6][6];
        float re0[6][1],re[6][1];
    }elm[50];


    ///input elements properties
    i=0;
    int sjoint,ejoint;
    while(i<ELN){

        printf("please enter starting joint number of element %d: \n",i+1);
        scanf("%d",&sjoint);
        elm[i].JN[0]=sjoint-1;
        printf("please enter ending joint number of element %d: \n",i+1);
        scanf("%d",&ejoint);
        elm[i].JN[1]=ejoint-1;
        if(strtype<4){
            elm[i].type=strtype;
        }
        else{
            printf("please enter the type of element %d : \n 1-truss \n 2-beam \n 3-column \n",i+1);
            scanf("%d",&elm[i].type);
        }

        if(elm[i].type==1){
            elm[i].I=pow(1000,15);
            for(j=0;j<=1;j++){
                elm[i].dof[(2*j)]=elm[i].DOF[j][0]=n[elm[i].JN[j]].DOF[0];
                elm[i].dof[(2*j)+1]=elm[i].DOF[j][1]=n[elm[i].JN[j]].DOF[1];
            }
        }
        if(elm[i].type==2){
                elm[i].A=pow(1000,15);
                for(j=0;j<=1;j++){
                elm[i].dof[(3*j)]=elm[i].DOF[j][0]=n[elm[i].JN[j]].DOF[0];
                elm[i].dof[(3*j)+1]=elm[i].DOF[j][1]=n[elm[i].JN[j]].DOF[1];
                elm[i].dof[(3*j)+2]=elm[i].DOF[j][2]=n[elm[i].JN[j]].DOF[2];
            }
        }
        if(elm[i].type==2){
                elm[i].A=pow(1000,15);
                for(j=0;j<=1;j++){
                elm[i].dof[(3*j)+0]=elm[i].DOF[j][0]=n[elm[i].JN[j]].DOF[0];
                elm[i].dof[(3*j)+1]=elm[i].DOF[j][1]=n[elm[i].JN[j]].DOF[1];
                elm[i].dof[(3*j)+2]=elm[i].DOF[j][2]=n[elm[i].JN[j]].DOF[2];
            }
        }


        ///element coordination,L,C,S calculations
        float x,y;

        elm[i].coord[0][0]=n[elm[i].JN[0]].coord[0];
        elm[i].coord[0][1]=n[elm[i].JN[0]].coord[1];
        elm[i].coord[1][0]=n[elm[i].JN[1]].coord[0];
        elm[i].coord[1][1]=n[elm[i].JN[1]].coord[1];

        y=(elm[i].coord[1][1]-elm[i].coord[0][1]);
        x=(elm[i].coord[1][0]-elm[i].coord[0][0]);

        elm[i].L=sqrt((x*x)+(y*y));
        elm[i].C=x/elm[i].L;
        elm[i].S=y/elm[i].L;

        i++;

    }



    ///element E,I,A
    i=0;
    int elmnum;
    int flag;
    while(i<material){
        flag=1;
        printf("please enter elements with material %d and enter (0) when finished: \n",i+1);
        while(flag==1){
            scanf("%d",&elmnum);
            if(elmnum==0)
                flag=0;
            else
                (elm[elmnum-1].E)=(E[i]);
        }
        i++;
    }

    i=0;
    while(i<inertia){
        flag=1;
        printf("please enter elements with inertia %d and enter (0) when finished: \n",i+1);
        while(flag==1){
            scanf("%d",&elmnum);
            if(elmnum==0)
                flag=0;
            else
                elm[elmnum-1].I=I[i];
        }
        i++;
    }

    i=0;
    while(i<area){
        flag=1;
        printf("please enter elements with Area %d and enter (0) when finished: \n",i+1);
        while(flag==1){
            scanf("%d",&elmnum);
            if(elmnum==0)
                flag=0;
            else
                elm[elmnum-1].A=A[i];
        }
        i++;
    }








    ///section 4 : local stiffness and coordinate transformation -------------------------------------------------------------------------------------------------
    printf("\n\n\n section 4 : local stiffness and coordinate transformation -------------------------------------------------------------------------------------------------\n\n\n");



    ///creation of k0 matrix
    i=0;
    counter=0;
    int sign;
    float k0[4][4];
    float marker;

    while(counter<ELN){
        if(elm[counter].type==2){
                k0[0][0]=12;
                k0[0][2]=12;
                k0[2][0]=12;
                k0[2][2]=12;
                k0[0][1]=(6*(elm[counter].L));
                k0[0][3]=(6*(elm[counter].L));
                k0[1][0]=(6*(elm[counter].L));
                k0[1][2]=(6*(elm[counter].L));
                k0[2][1]=(6*(elm[counter].L));
                k0[2][3]=(6*(elm[counter].L));
                k0[3][0]=(6*(elm[counter].L));
                k0[3][2]=(6*(elm[counter].L));
                k0[1][1]=(4*(elm[counter].L)*(elm[counter].L));
                k0[3][3]=(4*(elm[counter].L)*(elm[counter].L));
                k0[1][3]=(2*(elm[counter].L)*(elm[counter].L));
                k0[3][1]=(2*(elm[counter].L)*(elm[counter].L));

                marker=(elm[counter].E)*(elm[counter].I)/((elm[counter].L)*(elm[counter].L)*(elm[counter].L));
                for(i=0;i<=3;i++){
                        for(j=0;j<=3;j++){
                            sign=1;
                            if(((j==2)||(i==2))&&(i*j!=4)){
                                    sign=sign-2;
                            }
                            elm[counter].k0[i][j]=sign*marker*k0[i][j];
                        }

                }
        }

        if(elm[counter].type==1){
            marker=(elm[counter].E*elm[counter].A)/(elm[counter].L);
            for(i=0;i<=3;i++){
                for(j=0;j<=3;j++){
                   elm[counter].k0[i][j]=0;
                   if(i%2==0&&j%2==0){
                        elm[counter].k0[i][j]=1;
                   }
                   sign=1;
                   if(((j==2)||(i==2))&&(i*j!=4)&&(elm[counter].k0[i][j]!=0)){
                         sign=sign-2;
                   }
                   elm[counter].k0[i][j]=sign*marker*elm[counter].k0[i][j];
                }
            }
        }
        if(elm[counter].type==3){
            for(i=0;i<=5;i++){
                for(j=0;j<=5;j++){
                    elm[counter].k0[i][j]=0;
                }
            }
            elm[counter].k0[0][0]=elm[counter].k0[0][3]=elm[counter].k0[3][0]=elm[counter].k0[3][3]=((elm[counter].E)*(elm[counter].A))/(elm[counter].L);
            elm[counter].k0[1][1]=elm[counter].k0[1][4]=elm[counter].k0[4][1]=elm[counter].k0[4][4]=12;
            elm[counter].k0[1][2]=elm[counter].k0[1][5]=elm[counter].k0[2][1]=elm[counter].k0[2][4]=elm[counter].k0[4][2]=elm[counter].k0[4][5]=elm[counter].k0[5][1]=elm[counter].k0[5][4]=(6*elm[counter].L);
            elm[counter].k0[3][3]=elm[counter].k0[5][5]=4*elm[counter].L*elm[counter].L;
            elm[counter].k0[3][5]=elm[counter].k0[5][3]=2*elm[counter].L*elm[counter].L;

            for(i=0;i<=5;i++){
                for(j=0;j<=5;j++){
                    sign=1;
                    if(((j==4)||(i==4))&&(i*j!=16)){
                        sign=sign-2;
                    }
                    if((i==0)||(i==3)){
                        sign=pow(-1,i+j);
                    }
                    elm[counter].k0[i][j]=sign*elm[counter].k0[i][j];
                }
            }
        }

        counter++;
    }



    printf("\n\n\n\n");



    ///manual k0 input

    int row,col;
    int answerk0=0;

    printf("Are you willing to Input K0 Manually ? (0 = No , 1 = Yes)\n");
    scanf("%d",&answerk0);
    if(answerk0==1){
        while(elmnum>0){
            printf("enter number of element or enter 0 if you are done : \n");
            scanf("%d \n",&elmnum);
            printf("enter number of rows and columns : \n");
            scanf("%d \n",&row);
            scanf("%d \n",&col);
            for(i=0;i<row;i++){
                    printf("enter k0 matrix row %d : \n",i+1);
                    for(j=0;j<col;j++){
                            scanf("%f",&elm[elmnum].k0[i][j]);
                    }
            }
        }
    }








    ///creation of alpha matrix

    counter=0;
    while(counter<ELN){
        if(elm[counter].type==1){
            for(i=0;i<=3;i++){
                for(j=0;j<=3;j++){
                    elm[counter].alpha[i][j]=0;
                }
            }
            elm[counter].alpha[0][0]=elm[counter].alpha[2][2]=elm[counter].C;
            elm[counter].alpha[0][1]=elm[counter].alpha[2][3]=elm[counter].S;
        }
        if(elm[counter].type==2){
            for(i=0;i<=3;i++){
                for(j=0;j<=5;j++){
                    elm[counter].alpha[i][j]=0;
                }
            }
            elm[counter].alpha[0][0]=elm[counter].alpha[2][3]=(elm[counter].S)*(-1);
            elm[counter].alpha[0][1]=elm[counter].alpha[2][4]=elm[counter].C;
            elm[counter].alpha[1][2]=elm[counter].alpha[3][5]=1;

        }
        if(elm[counter].type==3){
            for(i=0;i<=5;i++){
                for(j=0;j<=5;j++){
                    elm[counter].alpha[i][j]=0;
                }
                elm[counter].alpha[i][i]=elm[counter].C;
            }
            elm[counter].alpha[0][1]=elm[counter].alpha[3][4]=elm[counter].S;
            elm[counter].alpha[1][0]=elm[counter].alpha[4][3]=(elm[counter].S)*(-1);
            elm[counter].alpha[2][2]=elm[counter].alpha[5][5]=1;

        }
        counter++;
    }




    ///manual alpha input

    row=0;
    col=0;
    int answeralpha=0;
    printf("Are you willing to Input Alpha matrix Manually ? (0 = No , 1 = Yes)\n");
    scanf("%d",&answeralpha);
    if(answeralpha==1){
        while(elmnum>0){
            printf("enter number of element or enter 0 if you are done : \n");
            scanf("%d \n",&elmnum);
            printf("enter number of rows and columns : \n");
            scanf("%d \n",&row);
            scanf("%d \n",&col);
            for(i=0;i<row;i++){
                    printf("enter Alpha matrix row %d : \n",i+1);
                    for(j=0;j<col;j++){
                            scanf("%f",&elm[elmnum].alpha[i][j]);
                    }
            }
        }
    }






    ///creation of global element k matrix

    float sum;
    counter=0;
    int ii=0;
    float test[6][6];

    while(counter<ELN){
        if(elm[counter].type==1){
            for(i=0;i<=3;i++){
                for(j=0;j<=3;j++){
                    sum=0;
                    for(ii=0;ii<=3;ii++){
                        sum=(elm[counter].alpha[ii][i])*(elm[counter].k0[ii][j])+sum;
                    }
                    test[i][j]=sum;
                }
            }
            for(i=0;i<=3;i++){
                for(j=0;j<=3;j++){
                    sum=0;
                    for(ii=0;ii<=3;ii++){
                        sum=(test[i][ii])*(elm[counter].alpha[ii][j])+sum;
                    }
                    elm[counter].k[i][j]=sum;
                }
            }
        }

        if(elm[counter].type==2){
            for(i=0;i<=5;i++){
                for(j=0;j<=3;j++){
                    sum=0;
                    for(ii=0;ii<=3;ii++){
                        sum=(elm[counter].alpha[ii][i])*(elm[counter].k0[ii][j])+sum;
                    }
                    test[i][j]=sum;
                }
            }
            for(i=0;i<=5;i++){
                for(j=0;j<=5;j++){
                    sum=0;
                    for(ii=0;ii<=3;ii++){
                        sum=(test[i][ii])*(elm[counter].alpha[ii][j])+sum;
                    }
                    elm[counter].k[i][j]=sum;
                }
            }
        }

        if(elm[counter].type==3){
            for(i=0;i<=5;i++){
                for(j=0;j<=5;j++){
                    sum=0;
                    for(ii=0;ii<=5;ii++){
                        sum=(elm[counter].alpha[ii][i])*(elm[counter].k0[ii][j])+sum;
                    }
                    test[i][j]=sum;
                }
            }
            for(i=0;i<=5;i++){
                for(j=0;j<=5;j++){
                    sum=0;
                    for(ii=0;ii<=5;ii++){
                        sum=(test[i][ii])*(elm[counter].alpha[ii][j])+sum;
                    }
                    elm[counter].k[i][j]=sum;
                }
            }
        }
        counter++;
    }









    ///section 5 : Elements info -------------------------------------------------------------------------------------------------
    printf("\n\n\n section 5 : Elements info -------------------------------------------------------------------------------------------------\n\n\n");

    counter=0;
    while(counter<ELN){
        printf("<<Element number %d>> \n\n",counter+1);
        switch (elm[counter].type){
        case 1:
            printf("Type : Truss \n");
            printf("Between joint%d and Join%d \n\n",elm[counter].JN[0]+1,elm[counter].JN[1]+1);
            printf("L=%f \t\t (EA/L)=%f \n\n",elm[counter].L,((elm[counter].E)*(elm[counter].A)/(elm[counter].L)));
            printf("Alpha Matrix: \n");
            for(i=0;i<=3;i++){
                for(j=0;j<=3;j++){
                    printf("%f \t",elm[counter].alpha[i][j]);
                }
                printf("\n\n");
            }
            printf("k0 Matrix: \n");
            for(i=0;i<=3;i++){
                for(j=0;j<=3;j++){
                    printf("%f \t",elm[counter].k0[i][j]);
                }
                printf("\n\n");
            }
            printf("k Matrix: \n");
            for(i=0;i<=3;i++){
                for(j=0;j<=3;j++){
                    printf("%f \t",elm[counter].k[i][j]);
                }
                printf("\n\n");
            }
            break;
        case 2:
            printf("Type : Beam \n");
            printf("Between joint%d and Join%d \n\n",elm[counter].JN[0]+1,elm[counter].JN[1]+1);
            printf("L=%f \t\t (EI/L3)=%f \n\n",elm[counter].L,((elm[counter].E)*(elm[counter].I)/(elm[counter].L*elm[counter].L*elm[counter].L)));
            printf("Alpha Matrix: \n");
            for(i=0;i<=3;i++){
                for(j=0;j<=5;j++){
                    printf("%f \t",elm[counter].alpha[i][j]);
                }
                printf("\n\n");
            }
            printf("k0 Matrix: \n");
            for(i=0;i<=3;i++){
                for(j=0;j<=3;j++){
                    printf("%f \t",elm[counter].k0[i][j]);
                }
                printf("\n\n");
            }
            printf("k Matrix: \n");
            for(i=0;i<=5;i++){
                for(j=0;j<=5;j++){
                    printf("%f \t",elm[counter].k[i][j]);
                }
                printf("\n\n");
            }
            break;
        case 3:
            printf("Type : Column \n");
            printf("Between joint%d and Join%d \n\n",elm[counter].JN[0]+1,elm[counter].JN[1]+1);
            printf("L=%f \t\t (EI/L3)=%f \tt (EA/L)=%f \n\n",(elm[counter].L),((elm[counter].E)*(elm[counter].I)/(elm[counter].L*elm[counter].L*elm[counter].L)),((elm[counter].E)*(elm[counter].A)/(elm[counter].L)));
            printf("Alpha Matrix: \n");
            for(i=0;i<=5;i++){
                for(j=0;j<=5;j++){
                    printf("%f \t",elm[counter].alpha[i][j]);
                }
                printf("\n\n");
            }
            printf("k0 Matrix: \n");
            for(i=0;i<=5;i++){
                for(j=0;j<=5;j++){
                    printf("%f \t",elm[counter].k0[i][j]);
                }
                printf("\n\n");
            }
            printf("k Matrix: \n");
            for(i=0;i<=5;i++){
                for(j=0;j<=5;j++){
                    printf("%f \t",elm[counter].k[i][j]);
                }
                printf("\n\n");
            }
            break;
        }

        printf("\n\n\n");
        counter++;
    }









    ///section 6 : structure equations and Obtaining Deformations -------------------------------------------------------------------------------------------------
    printf("\n\n\n section 6 : structure equations and Obtaining Deformations -------------------------------------------------------------------------------------------------\n\n\n");




    ///structure (struct)

    struct structure{
        float K[NDOF][NDOF],R[NDOF][1],D[NDOF][1],RE[NDOF][1];
        int connectivity[ELN][6];
    }mystr;


    ///connectivity matrix

    printf("\t\t\t");
    for(j=1;j<=6;j++){
        printf("%d\t",j);
    }
    printf("\n\n");

    for(i=0;i<ELN;i++){
        col=6;
        if(elm[i].type==1){
            col=4;
        }
        printf("element%d\t|\t",i+1);
        for(j=0;j<col;j++){
            mystr.connectivity[i][j]=elm[i].dof[j];
            printf("%d\t",mystr.connectivity[i][j]);
        }
        printf("\n");
    }


    printf("\n\n\n");
    ///structure K matrix

    printf("structure K matrix: \n\n");

    int numi[2],numj[2];
    int iii,jjj,jj;
    counter=0;
    float summ;

    for(i=1;i<=NDOF;i++){
        for(j=1;j<=NDOF;j++){
                iii=0;
                jjj=0;
                for(counter=0;counter<ELN;counter++){
                    summ=0;
                    for(ii=0;ii<6;ii++){
                        if(elm[counter].dof[ii]==i){
                            numi[iii]=ii;
                            iii++;
                        }
                    }
                    for(jj=0;jj<6;jj++){
                        if(elm[counter].dof[jj]==j){
                             numj[jjj]=jj;
                             jjj++;
                        }
                    }
                    for(iii=0;iii<2;iii++){
                        for(jjj=0;jjj<2;jjj++){
                            if((numj[iii]<10)&&(numj[jjj]<10)){
                                  summ=summ+elm[counter].k[numi[iii]][numj[jjj]];
                            }
                        }
                    }
                    mystr.K[i][j]=mystr.K[i][j]+summ;
                }
                printf("%f\t",mystr.K[i][j]);
        }
        printf("\n");
    }


    printf("\n\n\n\n Do you want to use this program again ? ( 1 = Yes , 0 = No ) \n");
    scanf("%d",&projectrepeat);
    }
    return 0;
}
