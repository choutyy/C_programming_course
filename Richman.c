#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h> //�ޤJ�r�����ջP�ഫ��Ƽ��Y��
#include <time.h>
#define TIME 200 * 1000
 
/*�]�w�}��*/
struct player_setting
{
    char *allname;
    int money;
    int current;
    int house[15];
    char name;
    int turns;
    int cards[5];
    int price;
 
} player, computer;
/*��Ƥ޼ư�*/
struct player_setting;
int map(char *[], char *[], int);
int ahead(int, int, char *[], char *[], char, int *);
int back(int, int, char *[], char *[], char);
int estate(int *, int *, int, int[], int[], int, int, int *, int *, char *[], char *[], char);
int carduse(int *, int *, int[], int, int[], int[], int *, int *, char *[], int);
 
/*�D�{��*/
int main()
{
    printf(" ::::::::::::::::::::::::\n");
    printf("  ::                  ::\n");
    printf("  ::    ��p��Ӫ�    ::\n");
    printf("  ::  �j �I �� �_ �I  ::\n");
    printf("  ::    (�Ψa��?)     ::\n");
    printf("  ::                  ::\n");
    printf(" ::::::::::::::::::::::::\n\n");
    printf("Press Any Key to start...\n");
    getchar();
    system("cls");
    char e[] = "�̦~,�A����O�q��";
    for (int i = 0; e[i] != '\0'; i++)
    {
        printf("%c", e[i]);
        usleep(TIME);
    }
    usleep(TIME * 10);
    printf("\b ");
    for (int i = 1; i < sizeof(e); i++)
    {
        printf("\b\b ");
        usleep(TIME);
    }
    char f[] = "�ӳ���W�ͩR���_�I�a";
    for (int i = 0; f[i] != '\0'; i++)
    {
        printf("%c", f[i]);
        usleep(TIME);
    }
    usleep(TIME * 20);
    system("cls");
 
    printf("�O�_�N�ͩR�I����5000�U�{�� [1]yes ");
    int ans;
    scanf("%d", &ans);
    if (ans != 1)
    {
        printf("�N��A����L��]�O�u��YES���ﶵ��^_^\n");
        usleep(TIME * 20);
    }
    system("cls");
 
    FILE *fp;
 
    char *located[] = {"   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   ", "   "};
    char *property[] ={"   ","   ","   ","   ","   ","   ","   ","   ","   ","   ","   ","   ","   ","   ","   ",};
    int choice;
    int fang(int turns);
    int  c;
    int goahead = 0;
    int Ppass = 1, Cpass = 1;
    int chance = 0;
    char *dice[] = {"[ �P ]", "[�P �P]", "[�P :]", "[: :]", "[:�P:]", "[:::]"};
    // int Q =0 ;
 
    srand((unsigned)time(NULL));
 
    char player_allname[10];
    printf("�п�J�A���W�r:\n");
    getchar();
    gets(player_allname);
    //printf("%d",strlen(player_allname));
    while (strlen(player_allname) <= 0 ||strlen(player_allname) > 10)
    {
        if (strlen(player_allname) > 10)
        {
            printf("�A���W�r�]�Ӫ��F�a�A�ְO�o�_�Ӱ�\n");
            printf("���u�@�I�a:\n");
            gets(player_allname);
        }
        else if (strlen(player_allname) <= 0)
        {
            printf("�A�S���W�r�ܡA�ӥi���F�a\n");
            printf("�٬O���@�Ӱ�:\n");
            gets(player_allname);
        }
    }

    if(strcmp(player_allname, "���ڨ�") == 0){
        printf("�u�O���A�S��k�A���N�s�A�p�¦n�F\n");
        strcpy(player_allname,"�p��");
        system("pause") ;
    }
start:
    system("cls");
    struct player_setting player = {player_allname, 5000, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 'p', 1, {0, 0, 0, 0, 0}};
    printf("     ^ ^\n   ( �PH�P )\n  o.�@   .o\n    O___O        %s ", player.allname);
    printf("�N��:%c\n", player.name);
    printf("�@�L�O�B�A�N�O�Ӫ��b\n\n");
    struct player_setting computer = {"Maou", 5000, 0, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 'c', 1, {0, 0, 0, 0, 0}};
 
    printf("   C_\\ \n�@  \\ \\(\\   /)\n�@   \\ (�CV�C) \n�@�@�@>  �@n \\ \n�@�@�@/ �@ A  \\ \n�@�@ /�@�@/ \\  \\ \n�@�@ L�@ /�@ \\_L) \n�@�@/�@/ \n�@ /�@/| \n�@(�@(\\ \n�@|�@|�B \n�@| /  �]  ) \n�@| |�@�@) / \n  / )�@�@L/       %s ", computer.allname);
    printf("�N��:%c\n", computer.name);
    printf("�R���C�����]��");
    getchar();
turn:
    if (player.money<=0)
    {
        printf("�A�ӺɤF�A���겣");
        system("pause");
        goto end;
    }
    if (computer.money<=0)
    {
        printf("Maou�ӺɤF�겣");
        system("pause");
        goto end;
    }
    else if (computer.money>10000)
    {
        printf("Maou�쵸�a���Ȧ�N�A�������]���S��\n");
        printf("Maou-5000�U %s -7000�U\n",player.allname);
        computer.money -= 5000;
        player.money -= 7000;
        system("pause");
        goto turn;
    }
    if (player.turns)
    {
        Ppass = 1;
        for (Cpass; Cpass > 0; Cpass--)
        {
            system("cls");
            if (player.current == computer.current)
            {
                char str[4];
                str[0] = player.name;
                str[1] = ' ';
                str[2] = computer.name;
                str[3] = '\0';
                located[player.current] = str;
            }
            else
            {
                char Pstr[4];
                char Cstr[4];
                Pstr[0] = player.name;
                Pstr[1] = ' ';
                Pstr[2] = ' ';
                Pstr[3] = '\0';
                Cstr[0] = computer.name;
                Cstr[1] = ' ';
                Cstr[2] = ' ';
                Cstr[3] = '\0';
                located[player.current] = Pstr;
                located[computer.current] = Cstr;
            }
            chance = 0;
            map(located, property, chance);
            printf("\n%s:%d�U��  %s:%d�U��\n", player_allname, player.money, computer.allname, computer.money);
            printf("----------------------------------------\n");
            printf("�п�ܾާ@:0.�s�� 1.���l 2.�ϥΥd�� 3.Ū�� 4.�C������ 5.�����C��...\n");
 
            scanf("%d", &choice);
            if (choice == 0)
            {
                fp = fopen(player.allname, "w");
                fwrite(&player, sizeof(struct player_setting), 1, fp);
                fwrite(&computer, sizeof(struct player_setting), 1, fp);
                fclose(fp);
                goto turn;
            }
            else if (choice == 5){
                return 0;
            }
            else if (choice == 4){
                printf("�S����C���W�h�A��۹C�����N��F�A�����ùC������\n��?�A�ݥd�����@��?\n�i�D�A�N�S�N��F�A�ۤv�h�����a<3\n");
                system("pause");
                goto turn;
            }
            else if (choice == 3)
            {
                for (int i = 0; i < 15; i++)
                {
                    located[i] = "   ";
                    property[i] = "   ";
                }
                fp = fopen(player.allname, "r");
                if (NULL == fp)
                {
                    printf("Open failure\n");
                    system("pause");
                    goto turn;
                }
                else
                {
                    fread(&player, sizeof(struct player_setting), 1, fp);
                    fread(&computer, sizeof(struct player_setting), 1, fp);
                }
                fclose(fp);
                for (int i = 0; i < 15; i++)
                {
                    if (player.house[i] == 1)
                    {
                        property[i] = "p0 ";
                    }
                    else if (player.house[i] == 2)
                    {
                        property[i] = "p1 ";
                    }
                    else if (player.house[i] == 3)
                    {
                        property[i] = "p2 ";
                    }
                    if (computer.house[i] == 1)
                    {
                        property[i] = "c0 ";
                    }
                    else if (computer.house[i] == 2)
                    {
                        property[i] = "c1 ";
                    }
                    else if (computer.house[i] == 3)
                    {
                        property[i] = "c2 ";
                    }
                }
                goto turn;
            }
            else if (choice == 2)
            {
                carduse(&computer.price, &player.price, player.cards, Cpass, player.house, computer.house, &player.money, &computer.money, property, computer.allname);
                goto turn;
            }
 
            else if (choice == 1)
            {
                for (int i = 0; i < 20; i++)
                {
                    goahead = rand() % 6;
                    printf("%s", dice[goahead]);
                    usleep(10 * 1000);
                    printf("\b\b\b\b\b");
                } /*ptestgo*/
                //goahead = 0;
                printf("%s�e�i%d��\n", dice[goahead], goahead + 1);
                system("pause");
                goahead = goahead + 1;
                player.current = ahead(goahead, player.current, located, property, player.name, &player.money);
                //system("cls");
                located[player.current] = &player.name;
 
                if (player.current == computer.current)
                {
                    char str[4];
                    str[0] = player.name;
                    str[1] = ' ';
                    str[2] = computer.name;
                    str[3] = '\0';
                    located[player.current] = str;
                }
                else
                {
                    char Pstr[4];
                    char Cstr[4];
                    Pstr[0] = player.name;
                    Pstr[1] = ' ';
                    Pstr[2] = ' ';
                    Pstr[3] = '\0';
                    Cstr[0] = computer.name;
                    Cstr[1] = ' ';
                    Cstr[2] = ' ';
                    Cstr[3] = '\0';
                    located[player.current] = Pstr;
                    located[computer.current] = Cstr;
                }
                map(located, property, chance);
                if (player.current == 8)
                {
                    int odds = rand() % 5;
                    //odds = 2;/*ptestch*/
                    chance = 1;
                    map(located, property, chance);
                    switch (odds)
                    {
                    case 0:
                        printf("�o��s�˰^�Y�A�M�۰^�Y���F�^�Y���G�m\n");
                        system("pause");
                        c = 2;
                        player.current = ahead(c, player.current, located, property, player.name, &player.money);
                        chance = 0;
                        map(located, property, chance);
                        estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                        break;
                    case 1:
                        printf("��o�䨧�G�A�P�򪺤H��A�h�פT��\n");
                        if (computer.current == 7 || computer.current == 8)
                        {
                            c = 3;
                            player.current = back(c, player.current, located, property, player.name);
                            estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                        }
                        else if (computer.current == 9)
                        {
                            c = 3;
                            player.current = ahead(c, player.current, located, property, player.name, &player.money);
                            estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                        }
                        system("pause");
                        break;
                    case 2:
                        printf("�ѭ��ֳ����Ǽu�A�A�Q����F,��2�^�X\n");
                        player.turns = 0;
                        Ppass = 3;
                        system("pause");
                        break;
                    case 3:
                        printf("���䪺���V�A�]�ӡA�A���J�X�n�����̭��L�k�۩�,��1�^�X\n");
                        player.turns = 0;
                        Ppass = 2;
                        system("pause");
                        break;
                    case 4:
                        printf("�q���e�һ�i�F�����ֳt�Ĩ�3��\n");
                        c = 3;
                        player.current = ahead(c, player.current, located, property, player.name, &player.money);
                        estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                        system("pause");
                        break;
                    }
                }
                else if (player.current == 12)
                {
                    int fate = rand() % 5;
                    //fate = 4;/*ptestf*/
                    chance = 2;
                    map(located, property, chance);
                    switch (fate) /*�R�B���*/
                    {
                    case 0:
                        printf("�Y��]�F���l������+500�U��\n");
                        player.money += 500;
                        system("pause");
                        break;
                    case 1:
                        printf("�E�足���Ѳ��j��+1000�U��\n");
                        player.money += 1000;
                        system("pause");
                        break;
                    case 2:
                        printf("�E�足���Ѳ��j�^-1500�U��\n");
                        player.money -= 1500;
                        system("pause");
                        break;
                    case 3:
                        printf("�Q�j�����P�R�ߵ�-500�U��\n");
                        player.money -= 500;
                        system("pause");
                        break;
                    case 4:
                        printf("�Q�������u\n");
                        int i, poker[15], temp, pos;
                        poker[0] = 15;
                        for (i = 0; i < 15; ++i)
                            poker[i] = i;
                        for (i = 0; i < 15; ++i)
                        {
                            pos = 14 * rand() / RAND_MAX;
                            temp = poker[i];
                            poker[i] = poker[pos];
                            poker[pos] = temp;
                        }
                        for (i = 0; i < 15; ++i)
                        {
                            if (player.house[poker[i]] == 1 || player.house[poker[i]] == 2|| player.house[poker[i]] == 3)
                            {
                                player.house[poker[i]] = 0;
                                property[poker[i]] = "\033[41m   \033[m";
                                printf("���W�H���@�ɩФl�Q���F\n");
                                break;
                            }
                            if (computer.house[poker[i]] == 1 || computer.house[poker[i]] == 2|| computer.house[poker[i]] == 3)
                            {
                                computer.house[poker[i]] = 0;
                                property[poker[i]] = "\033[41m   \033[m";
                                printf("���W�H���@�ɩФl�Q���F\n");
                                break;
                            }
                        }
                        usleep(TIME * 10);
                        break;
                    }
                }
                else if (player.current == 4)
                {
                    int buy;
                    int sure;
                    chance = 3;
                    map(located, property, chance);
                card:
                    printf("\n%s:%d�U��  %s:%d�U��\n", player_allname, player.money, computer.allname, computer.money);
                    printf("----------------------------------------\n");
                    printf("�w����{�d���ө��A�Q�n�R�I�����?(�п�J�Q�ʶR�d�����s��)\n");
                    scanf("%d", &buy);
                    switch (buy)
                    {
                    case 1:
                        printf("�O�_�n�ʶR�����s�O(����3000�U)? [1]�O[0]�_\n");
                        scanf("%d", &sure);
                        if (sure == 1)
                        {
                            if (player.money > 3000)
                            {
                                player.money -= 3000;
                                player.cards[0]++;
                                printf("��o�����s�A�z�������Ѿl%d\n", player.money);
                            }
                            else
                            {
                                printf("��p�z���l�B������\n");
                            }
                            goto card;
                        }
                        else
                        {
                            goto card;
                        }
                    case 2:
                        printf("�O�_�n�ʶR�n����O(����1500�U)? [1]�O[0]�_\n");
                        scanf("%d", &sure);
                        if (sure == 1)
                        {
                            if (player.money > 1500)
                            {
                                player.money -= 1500;
                                player.cards[1]++;
                                printf("��o�n����A�z�������Ѿl%d\n", player.money);
                            }
                            else
                            {
                                printf("��p�z���l�B������\n");
                            }
                            goto card;
                        }
                        else
                        {
                            goto card;
                        }
                    case 3:
                        printf("�O�_�n�ʶR���Ʀ׺�O(����1500�U)? [1]�O[0]�_\n");
                        scanf("%d", &sure);
                        if (sure == 1)
                        {
                            if (player.money > 1500)
                            {
                                player.money -= 1500;
                                player.cards[2]++;
                                printf("��o���Ʀ׺�\n");
                            }
                            else
                            {
                                printf("��p�z���l�B������\n");
                            }
                            goto card;
                        }
                        else
                        {
                            goto card;
                        }
                    case 4:
                        printf("�O�_�n�ʶR1450�O(����1450�U)? [1]�O[0]�_\n");
                        scanf("%d", &sure);
                        if (sure == 1)
                        {
                            if (player.money > 1450)
                            {
                                player.money -= 1450;
                                player.cards[3]++;
                                printf("��o1450�A�z�������Ѿl%d\n", player.money);
                            }
                            else
                            {
                                printf("��p�z���l�B������\n");
                            }
                            goto card;
                        }
                        else
                        {
                            goto card;
                        }
                    case 5:
                        printf("�O�_�n�ʶR8+9�O(����3000�U)? [1]�O[0]�_\n");
                        scanf("%d", &sure);
                        if (sure == 1)
                        {
                            if (player.money > 3000)
                            {
                                player.money -= 3000;
                                player.cards[4]++;
                                printf("��o8+9�A�z�������Ѿl%d\n", player.money);
                            }
                            else
                            {
                                printf("��p�z���l�B������\n");
                            }
                            goto card;
                        }
                        else
                        {
                            goto card;
                        }
                    default:
                        printf("�O�_�n���}�O? [1]�O[0]�_\n");
                        scanf("%d", &sure);
                        if (sure == 1)
                        {
                            break;
                        }
                        else
                        {
                            goto card;
                        }
                    }
                }
                else if (player.current == 0)
                {
                    printf("%s�V�Ȧ�U��2000�U\n", player_allname);
                    player.money += 2000;
                    system("pause");
                }
                else
                {
                    estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                }
            }
            else
            {
                printf("�K�A�зӤW�������ܥ����n�ÿ�J..\n");
                system("pause");
                goto turn;
            }
        }
        if (player.current == computer.current)
        {
            char str[4];
            str[0] = player.name;
            str[1] = ' ';
            str[2] = computer.name;
            str[3] = '\0';
            located[player.current] = str;
        }
        else
        {
            char Pstr[4];
            char Cstr[4];
            Pstr[0] = player.name;
            Pstr[1] = ' ';
            Pstr[2] = ' ';
            Pstr[3] = '\0';
            Cstr[0] = computer.name;
            Cstr[1] = ' ';
            Cstr[2] = ' ';
            Cstr[3] = '\0';
            located[player.current] = Pstr;
            located[computer.current] = Cstr;
        }
        chance = 0;
        map(located, property, chance);
        located[player.current] = " ";
        player.turns = 0;
        goto turn;
    }
    else
    { /*�]��*/
        Cpass = 1;
        for (Ppass; Ppass > 0; Ppass--)
        {
            system("cls");
            if (player.current == computer.current)
            {
                char str[4];
                str[0] = player.name;
                str[1] = ' ';
                str[2] = computer.name;
                str[3] = '\0';
                located[player.current] = str;
            }
            else
            {
                char Pstr[4];
                char Cstr[4];
                Pstr[0] = player.name;
                Pstr[1] = ' ';
                Pstr[2] = ' ';
                Pstr[3] = '\0';
                Cstr[0] = computer.name;
                Cstr[1] = ' ';
                Cstr[2] = ' ';
                Cstr[3] = '\0';
                located[player.current] = Pstr;
                located[computer.current] = Cstr;
            }
            map(located, property, chance);
            printf("\n%s:%d�U��  %s:%d�U��\n", player_allname, player.money, computer.allname, computer.money);
            printf("----------------------------------------\n");
            printf("Maou turn%d\n", Ppass);
            chance = 0;
            for (int i = 0; i < 20; i++)
            {
                goahead = rand() % 6;
                printf("%s", dice[goahead]);
                usleep(10 * 1000);
                printf("\b\b\b\b\b");
            }
            //goahead = 3; /*ctestgo*/
            printf("%s�e�i%d��\n", dice[goahead], goahead + 1);
            usleep(TIME * 10);
            goahead = goahead + 1;
            computer.current = ahead(goahead, computer.current, located, property, computer.name, &computer.money);
            //system("cls");
            located[computer.current] = &computer.name;
            if (computer.current == 8)
            {
                int odds = rand() % 5;
                //odds = 2;
                chance = 1;
                if (player.current == computer.current)
                {
                    char str[4];
                    str[0] = player.name;
                    str[1] = ' ';
                    str[2] = computer.name;
                    str[3] = '\0';
                    located[player.current] = str;
                }
                else
                {
                    char Pstr[4];
                    char Cstr[4];
                    Pstr[0] = player.name;
                    Pstr[1] = ' ';
                    Pstr[2] = ' ';
                    Pstr[3] = '\0';
                    Cstr[0] = computer.name;
                    Cstr[1] = ' ';
                    Cstr[2] = ' ';
                    Cstr[3] = '\0';
                    located[player.current] = Pstr;
                    located[computer.current] = Cstr;
                }
                map(located, property, chance);
                switch (odds)
                {
                case 0:
                    printf("Maou�o��s�˰^�Y�A�M�۰^�Y���F�^�Y���G�m\n");
                    usleep(TIME * 10);
                    c = 2;
                    computer.current = ahead(c, computer.current, located, property, computer.name, &computer.money);
                    estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                    break;
                case 1:
                    printf("Maou��o�䨧�G�A�P�򪺤H��Maou�h�פT��\n");
                    if (player.current == 7 || player.current == 8)
                    {
                        located[player.current] = "   ";
                        c = 3;
                        player.current = back(c, player.current, located, property, player.name);
                        estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                    }
                    else if (player.current == 9)
                    {
                        located[player.current] = "   ";
                        c = 3;
                        player.current = ahead(c, player.current, located, property, player.name, &player.money);
                        estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                    }
                    usleep(TIME * 10);
                    break;
                case 2:
                    printf("�ѭ��ֳ����Ǽu�AMaou�Q����F,��2�^�X\n");
                    player.turns = 1;
                    Cpass = 3;
                    chance = 0;
                    usleep(TIME * 10);
                    break;
                case 3:
                    printf("���䪺���VMaou�]�ӡAMaou���J�X�n�����̭��L�k�۩�,��1�^�X\n");
                    player.turns = 1;
                    Cpass = 2;
                    chance = 0;
                    usleep(TIME * 10);
                    break;
                case 4:
                    printf("Maou�q���e�һ�i�F�����ֳt�Ĩ�3��\n");
                    c = 3;
                    computer.current = ahead(c, computer.current, located, property, computer.name, &computer.money);
                    estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
                    usleep(TIME * 10);
                    break;
                }
            }
            else if (computer.current == 12)
            {
                int fate = rand() % 5;
                chance = 2; /*ctestf*/
                switch (fate)
                {
                case 0:
                    printf("Maou�Y��]�F���l������+500�U��\n");
                    computer.money += 500;
                    usleep(TIME * 10);
                    break;
                case 1:
                    printf("�E�足���Ѳ��j��+1000�U��\n");
                    computer.money += 1000;
                    usleep(TIME * 10);
                    break;
                case 2:
                    printf("�E�足���Ѳ��j�^-1500�U��\n");
                    computer.money -= 1500;
                    usleep(TIME * 10);
                    break;
                case 3:
                    printf("Maou�Q�j�����P�R�ߵ�-500�U��\n");
                    computer.money -= 500;
                    usleep(TIME * 10);
                    break;
                case 4:
                    printf("�Q�������u\n");
                    int i, poker[15], temp, pos;
                    poker[0] = 15;
                    for (i = 0; i < 15; ++i)
                        poker[i] = i;
                    for (i = 0; i < 15; ++i)
                    {
                        pos = 14 * rand() / RAND_MAX;
                        temp = poker[i];
                        poker[i] = poker[pos];
                        poker[pos] = temp;
                    }
                    for (i = 0; i < 15; ++i)
                    {
                        if (player.house[i] == 1 || player.house[i] == 2)
                        {
                            player.house[i] = 0;
                            property[i] = "\033[41m   \033[m";
                            printf("���W�H���@�ɩФl�Q���F\n");
                            break;
                        }
                        if (computer.house[i] == 1 || computer.house[i] == 2)
                        {
                            computer.house[i] = 0;
                            property[i] = "\033[41m   \033[m";
                            printf("���W�H���@�ɩФl�Q���F\n");
                            break;
                        }
                    }
                    usleep(TIME * 10);
                    break;
                }
            }
            else if (computer.current == 0)
            {
                //Cround++;
                printf("Maou�V�Ȧ�U��2000�U");
                computer.money += 2000;
                usleep(TIME * 10);
            }
            else if (computer.current == 4)
            {
                int buy = rand() % 5;
                //buy = 2; /*ctestc*/
                chance = 3;
                map(located, property, chance);
                if (computer.money > 3000)
                {
                    buy++;
                    switch (buy)
                    {
                    case 1:
                        computer.money -= 3000;
                        printf("Maou��o�����s\n");
                        int out = 0;
                        for (int i = 0; i < 15; i++)
                        {
                            if (player.house[i] == 1 || player.house[i] == 2|| player.house[i] == 3)
                            {
                                player.house[i] = 0;
                                out = 1;
                                property[i] = "\033[41m   \033[m";
                                printf("�ϥΤ����s�A%s���Фl�Q���F\n", player_allname);
                                usleep(TIME * 10);
                                break;
                            }
                        }
                        if (out == 0)
                        {
                            printf("�����s�C��F�@��,��W���H���ܶ}�ߡAMaou��o���o��4000��");
                            computer.money += 4000;
                            usleep(TIME * 10);
                            break;
                        }
                        else
                        {
                            break;
                        }
                    case 2:
                        computer.money -= 1500;
                        printf("��o�n����\n");
                        printf("Maou�N�@�i�n����e��%s�A��%s�Y��l�Y��Ȯ𨫤��ʡA�𮧤@�^�X\n", player_allname, player_allname);
                        Ppass++;
                        usleep(TIME * 10);
                        break;
 
                    case 3:
                        computer.money -= 1500;
                        printf("Maou��o���Ʀ׺�\n");
                        printf("�e�׺궤��g�L%s���a�A%s�U���Ҧ��L���O��b\n", player_allname, player_allname);
                        player.price = 1;
                        usleep(TIME * 10);
                        break;
 
                    case 4:
                        computer.money -= 1450;
                        printf("Maou��o1450\n");
                        printf("Maou����1450�A�U�������L���O�[��\n");
                        computer.price = 2;
                        usleep(TIME * 10);
                        break;
 
                    case 5:
                        computer.money -= 3000;
                        printf("Maou��o8+9\n");
                        printf("8+9�V%s�����O�@�O2000�U��\n", player_allname);
                        player.money -= 2000;
                        computer.money += 2000;
                        usleep(TIME * 10);
                        break;
 
                    default:
                        printf("Maou���}�F�d���ө�");
                        usleep(TIME * 10);                   
                        break;
                    }
                }
                else{
                    printf("Maou���}�F�d���ө�");
                    usleep(TIME * 10);
                }
            }
            else
            {
                estate(&player.price, &computer.price, player.turns, player.house, computer.house, player.current, computer.current, &player.money, &computer.money, located, property, player_allname);
            }
            if (player.current == computer.current)
            {
                char str[4];
                str[0] = player.name;
                str[1] = ' ';
                str[2] = computer.name;
                str[3] = '\0';
                located[player.current] = str;
            }
            else
            {
                char Pstr[4];
                char Cstr[4];
                Pstr[0] = player.name;
                Pstr[1] = ' ';
                Pstr[2] = ' ';
                Pstr[3] = '\0';
                Cstr[0] = computer.name;
                Cstr[1] = ' ';
                Cstr[2] = ' ';
                Cstr[3] = '\0';
                located[player.current] = Pstr;
                located[computer.current] = Cstr;
            }
            chance = 0;
            map(located, property, chance);
            located[computer.current] = " ";
        }
        player.turns = 1;
        goto turn;
    }
end:
    system("cls");
    if(computer.money<=0){
        printf("    ^  ^\n  ( �Pw�P �� (��)\n o.�@�@,/.  ||\n  �ݡ�./\n     (/\n     i|I    �iWIN�j\n    -----\n");
        printf("���ߧA����Maou��o����������A��o�L�W���O�q�æ������C\n");
        system("pause");
        system("cls");
        printf("�W�r�G%s\n", player.allname);
        printf("�֦��겣�G%d�U��\n", player.money);
    }
    else{
        char g[] = "�A�ӺɤF�ͩR�A�Y���b�L�ɪ��`�W...";
        for (int i = 0; g[i] != '\0'; i++)
        {
            printf("%c", g[i]);
            usleep(TIME);
        }
        printf("\n");
    }
    system("pause");
    goto trueend;
trueend:
    printf("�аݭn���s�}�l�C���ܡH [1]yes [2]no\n");
    int ans1;
    scanf("%d", &ans1);
    if (ans1 == 1){
        system("cls");
        goto start;
    }
    else if(ans1 == 2){
        return 0;
    }
    else{
        printf("�n�n���ӫ��O�O�����f\n");
        goto trueend;
    }
}
 
/*�w�q�e�i���*/
int map(char *[], char *[], int);
int ahead(int goahead, int current, char *located[], char *property[], char name, int *money)
{
    int b;
    located[current] = "   ";
    for (b = 0; b < goahead; b++)
    {
        current++;
        if (current >= 16)
        {
            printf("�g�L�a���Ȧ�A����Ȧ�o��2000�U�ɧU\n");
            *money += 2000;
            current = 0;
            usleep(TIME * 10);
        }
    }
    return current;
}
 
/*�w�q��h���*/
int map(char *[], char *[], int);
int back(int goback, int current, char *located[], char *property[], char name)
{
    int a, b;
    for (b = 0, a = 0; b < goback; b++)
    {
        if (current <= 0)
        {
            current = 0;
        }
        else
        {
            current = current - 1;
        }
    }
    return current;
}
 
/*�Цa��*/
struct player_setting;
int map(char *[], char *[], int);
int estate(int *pprice, int *cprice, int p_turns, int p_house[15], int c_house[15], int p_current, int c_current, int *p_money, int *c_money, char *located[], char *property[], char player_allname)
{
    int block = 0;
    int toll_land = 500;
    int toll_house1 = 1000;
    int toll_house2 = 1500;
    int a;
    if (p_turns == 1)
    {
        switch (p_current)
        {
        case 1:
            block = 0;
            break;
        case 2:
            block = 1;
            break;
        case 3:
            block = 2;
            break;
 
        case 5:
            block = 4;
            break;
        case 6:
            block = 5;
            break;
        case 7:
            block = 6;
            break;
 
        case 9:
            block = 8;
            break;
        case 10:
            block = 9;
            break;
        case 11:
            block = 10;
            break;
 
        case 13:
            block = 12;
            break;
        case 14:
            block = 13;
            break;
        case 15:
            block = 14;
            break;
 
        default:
            break;
        }
        if (c_house[block] == 0)
        {
            if (p_house[block] == 0)
            {
                if (*p_money >= 1500)
                {
                    printf("�z�{�b�ѤU%d�U���A�аݭn�ʶR�a�L�ܡH�ʶR�a�L��1500�U���C<1>��M�n�ʶR�I<���N��>�A�Q�Q�n�F\n", *p_money);
                    scanf("%d", &a);
                    if (a == 1)
                    {
                        p_house[block] = 1;
                        *p_money = *p_money - 1500;
                        property[block] = "p0 ";
                    }
                }
                else
                {
                    printf("�������{���~��e�i\n");
                    //break;
                }
            }
            else if (p_house[block] == 1)
            {
                if (*p_money >= 1000)
                {
                    printf("�z�{�b�ѤU%d�U���A�аݭn�سy�����u�ܡH�سy�����u��1000�U���C<1>���إդ��ءI<���N��>�A�Q�Q�n�F\n", *p_money);
                    scanf("%d", &a);
                    if (a == 1)
                    {
                        p_house[block] = 2;
                        *p_money = *p_money - 1000;
                        property[block] = "p1 ";
                    }
                }
                else
                {
                    printf("�������{���~��e�i");
                    //break;
                }
            }
            else if (p_house[block] == 2)
            {
                if (*p_money >= 1000)
                {
                    printf("�z�{�b�ѤU%d�U���A�аݭn�سy�����ܡH�سy������1000�U���C<1>�[�a�I<���N��>�A�Q�Q�n�F\n", *p_money);
                    scanf("%d", &a);
                    if (a == 1)
                    {
                        p_house[block] = 3;
                        *p_money = *p_money - 1000;
                        property[block] = "p2 ";
                    }
                }
                else
                {
                    printf("�������{���~��e�i");
                    //break;
                }
            }
            else
            {
                printf("�Цa���w��̰��ŧO�I\n");
            }
            //system("pause");
            //break;
        }
        else
        {
            if (*cprice == 0)
            {
                switch (c_house[block])
                {
                case 1:
                    printf("����Maou���a�L�A�ݤ�I500�U���L���O�C\n");
                    *c_money = *c_money + toll_land;
                    *p_money = *p_money - toll_land;
                    break;
                case 2:
                    printf("����Maou���@�h�СA�ݤ�I1000�U���L���O�C\n");
                    *c_money = *c_money + toll_house1;
                    *p_money = *p_money - toll_house1;
                    break;
                case 3:
                    printf("����Maou����h�СA�ݤ�I1500�U���L���O�C\n");
                    *c_money = *c_money + toll_house2;
                    *p_money = *p_money - toll_house2;
                    break;
                default:
                    break;
                }
            }
            if (*cprice == 1)
            {
                switch (c_house[block])
                {
                case 1:
                    printf("����Maou���a�L�A�ݤ�I250�U���L���O�C\n");
                    *c_money = *c_money + toll_land / 2;
                    *p_money = *p_money - toll_land / 2;
                    *cprice = 0;
                    break;
                case 2:
                    printf("����Maou���@�h�СA�ݤ�I500�U���L���O�C\n");
                    *c_money = *c_money + toll_house1 / 2;
                    *p_money = *p_money - toll_house1 / 2;
                    *cprice = 0;
                    break;
                case 3:
                    printf("����Maou����h�СA�ݤ�I750�U���L���O�C\n");
                    *c_money = *c_money + toll_house2 / 2;
                    *p_money = *p_money - toll_house2 / 2;
                    *cprice = 0;
                    break;
                default:
                    break;
                }
            }
            if (*cprice == 2)
            {
                switch (c_house[block])
                {
                case 1:
                    printf("����Maou���a�L�A�ݤ�I1000�U���L���O�C\n");
                    *c_money = *c_money + toll_land * 2;
                    *p_money = *p_money - toll_land * 2;
                    *cprice = 0;
                    break;
                case 2:
                    printf("����Maou���@�h�СA�ݤ�I2000�U���L���O�C\n");
                    *c_money = *c_money + toll_house1 * 2;
                    *p_money = *p_money - toll_house1 * 2;
                    *cprice = 0;
                    break;
                case 3:
                    printf("����Maou����h�СA�ݤ�I3000�U���L���O�C\n");
                    *c_money = *c_money + toll_house2 * 2;
                    *p_money = *p_money - toll_house2 * 2;
                    *cprice = 0;
                    break;
                default:
                    break;
                }
            }
        }
        system("pause");
        // break;
    }
    else
    {
        switch (c_current)
        {
        case 1:
            block = 0;
            break;
        case 2:
            block = 1;
            break;
        case 3:
            block = 2;
            break;
 
        case 5:
            block = 4;
            break;
        case 6:
            block = 5;
            break;
        case 7:
            block = 6;
            break;
 
        case 9:
            block = 8;
            break;
        case 10:
            block = 9;
            break;
        case 11:
            block = 10;
            break;
 
        case 13:
            block = 12;
            break;
        case 14:
            block = 13;
            break;
        case 15:
            block = 14;
            break;
 
        default:
            break;
        }
        if (p_house[block] == 0)
        {
            if (*c_money >= 1500)
            {
                switch (c_house[block])
                {
                case 0:
                    printf("Maou�H1500�U���ʤU�Ӧa�L�I\n");
                    c_house[block] = 1;
                    *c_money = *c_money - 1500;
                    property[block] = "c0 ";
                    break;
                case 1:
                    printf("Maou�H1000�U���سy�����u�I\n");
                    c_house[block] = 2;
                    *c_money = *c_money - 1000;
                    property[block] = "c1 ";
                    break;
                case 2:
                    printf("Maou�H1000�U���سy�����I\n");
                    c_house[block] = 3;
                    *c_money = *c_money - 1000;
                    property[block] = "c2 ";
                    break;
                case 3:
                    printf("Maou���Фw�F�̰����šI\n");
                    break;
                default:
                    break;
                }
            }
            else
            {
                printf("Maou:�S���R�СA�A��");
            }
            system("pause");
            // break;
        }
        else
        {
            if (*pprice == 0)
            {
                switch (p_house[block])
                {
                case 1:
                    printf("Maou����A���a�L�A��I500�U���L���O�C\n");
                    *c_money = *c_money - toll_land;
                    *p_money = *p_money + toll_land;
                    break;
                case 2:
                    printf("Maou����A���@�h�СA��I1000�U���L���O�C\n");
                    *c_money = *c_money - toll_house1;
                    *p_money = *p_money + toll_house1;
                    break;
                case 3:
                    printf("Maou����A����h�СA��I1500�U���L���O�C\n");
                    *c_money = *c_money - toll_house2;
                    *p_money = *p_money + toll_house2;
                    break;
                default:
                    break;
                }
            }
            else if (*pprice == 1)
            {
                switch (p_house[block])
                {
                case 1:
                    printf("Maou����A���a�L�A��I250�U���L���O�C\n");
                    *c_money = *c_money - toll_land / 2;
                    *p_money = *p_money + toll_land / 2;
                    *pprice = 0;
                    break;
                case 2:
                    printf("Maou����A���a�L�A��I500�U���L���O�C\n");
                    *c_money = *c_money - toll_house1 / 2;
                    *p_money = *p_money + toll_house1 / 2;
                    *pprice = 0;
                    break;
                case 3:
                    printf("Maou����A����h�СA��I750�U���L���O�C\n");
                    *c_money = *c_money - toll_house2 / 2;
                    *p_money = *p_money + toll_house2 / 2;
                    *pprice = 0;
                    break;
                default:
                    break;
                }
            }
            else if (*pprice == 2)
            {
                switch (p_house[block])
                {
                case 1:
                    printf("Maou����A���a�L�A��I1000�U���L���O�C\n");
                    *c_money = *c_money - toll_land * 2;
                    *p_money = *p_money + toll_land * 2;
                    *pprice = 0;
                    break;
                case 2:
                    printf("Maou����A���@�h�СA��I2000�U���L���O�C\n");
                    *c_money = *c_money - toll_house1 * 2;
                    *p_money = *p_money + toll_house1 * 2;
                    *pprice = 0;
                    break;
                case 3:
                    printf("Maou����A����h�СA��I3000�U���L���O�C\n");
                    *c_money = *c_money - toll_house2 * 2;
                    *p_money = *p_money + toll_house2 * 2;
                    *pprice = 0;
                    break;
                default:
                    break;
                }
            }
            system("pause");
            // break;
        }
    }
    return 0;
}
 
/*�d��*/ /*card,turn,house*2,money,property,name*/
int carduse(int *cprice, int *pprice, int card[5], int turns, int my_house[15], int you_house[15], int *my_money, int *you_money, char *property[], int allname)
{
    int use;
    printf("�A�֦����d��:\n");
    if (card[0] >= 1)
    {
        printf("1.�����s ");
    }
    if (card[1] >= 1)
    {
        printf("2.�n���� ");
    }
    if (card[2] >= 1)
    {
        printf("3.���Ʀ׺� ");
    }
    if (card[3] >= 1)
    {
        printf("4.1450 ");
    }
    if (card[4] >= 1)
    {
        printf("5.8+9 ");
    }
    if (card[0] == 0 && card[2] == 0 && card[3] == 0 && card[4] == 0 && card[1] == 0)
    {
        printf("��p�A�S���d���O");
        system("pause");
        return 0;
    }
used:
    printf("\n�Q�ϥΤ���d���O");
    scanf("%d", &use);
    switch (use)
    {
    case 1:
        if (card[0] >= 1)
        {
            card[0] --;
            for (int i = 0; i < 15; i++)
            {
                if (you_house[i] == 1 || you_house[i] == 2 || you_house[i] == 3)
                {
                    you_house[i] = 0;
                    property[i] = "\033[41m   \033[m";
                    printf("�ϥΤ����s�A%s���Фl�Q���F\n", allname);
                    system("pause");
                    return 0;
                }
                else
                {
                    continue;
                }
            }
            printf("�����s�C��F�@��,��W���H���ܶ}��,��o���o��4000��");
            system("pause");
            *my_money += 4000;
        }
        else
        {
            printf("��p�A�S���o�i�d");
            system("pause");
            goto used;
        }
        break;
    case 2:
        if (card[1] >= 1)
        {
            card[1]--;
            printf("�N�@�i�n����e��%s�A�Ϥ���l�Y��Ȯ𨫤��ʡA�𮧤@�^�X\n", allname);
            turns++;
            system("pause");
            return turns;
        }
        else
        {
            printf("��p�A�S���o�i�d");
            system("pause");
            goto used;
        }
        break;
    case 3:
        if (card[2] >= 1)
        {
            card[2]--;
            printf("�e�׺궤��g�LMaou���a�AMaou�U�������L���O��b\n");
            *cprice = 1; /*��в�*/
            system("pause");
            return 0;
        }
        else
        {
            printf("��p�A�S���o�i�d");
            system("pause");
            goto used;
        }
        break;
    case 4:
        if (card[3] >= 1)
        {
            card[3]--;
            printf("����1450�A�U�������L���O�[��\n");
            *pprice = 2;
            system("pause");
            return 0;
        }
        else
        {
            printf("��p�A�S���o�i�d");
            system("pause");
            goto used;
        }
        break;
    case 5:
        if (card[4] >= 1)
        {
            card[4]--;
            printf("8+9�V%s�����O�@�O2000�U��\n", allname);
            *you_money -= 2000;
            *my_money += 2000;
            return 0;
        }
        else
        {
            printf("��p�A�S���o�i�d");
            system("pause");
            goto used;
        }
        break;
    default:
        break;
    }
    return 0;
}
 
/*�a�ϴyø*/
int map(char *located[], char *property[], int chance)
{
    char *a[] = {"\033[45m+----------------+\033[m", "\033[45m|                |\033[m", "\033[45m| ************** |\033[m", "\033[45m|  # ��    �| #  |\033[m", "\033[45m| ************** |\033[m", "\033[45m|                |\033[m", "\033[45m|        @       |\033[m", "\033[45m|     @     @    |\033[m", "\033[45m|  ~~~~~~~~~~~~  |\033[m", "\033[45m|                |\033[m", "\033[45m+----------------+\033[m"};
    char *b[] = {"\033[45m+----------------+\033[m", "\033[45m|                |\033[m", "\033[45m| ************** |\033[m", "\033[45m|  @ �R    �B @  |\033[m", "\033[45m| ************** |\033[m", "\033[45m|                |\033[m", "\033[45m|        $       |\033[m", "\033[45m|    $   O   $   |\033[m", "\033[45m|        $       |\033[m", "\033[45m|                |\033[m", "\033[45m+----------------+\033[m"};
    char *c[] = {"                  ", "                  ", "                  ", "                  ", "                  ", "                  ", "                  ", "                  ", "                  ", "                  ", "                  "};
    char *d[] = {" +_______________+", "  /             \\ ", " /  �d �� �� ��  \\", "/_               _\\", "  |  1. �����s  | ", "  |  2. �n����  | ", "  |  3. ���Ʀ׺�| ", "  |  4. 1450    | ", "  |  5. 8 + 9   | ", "  |  \033[36m[0] ���}\033[m   | ", " -----------------"};
    if (chance == 1)
    {
        for (int i = 0; i < 12; i++)
        {
            c[i] = a[i];
            system("cls");
            printf("==============================================\n");
            printf("|\033[33m��    �|\033[m|�] �� ��|�^ �Y ��|��    �c|\033[33m�R    �B\033[m|\n");
            printf("|%s     |%s     |%s     |%s     |%s     |\n", property[7], property[8], property[9], property[10], property[11]);
            printf("|%s     |%s     |%s     |%s     |%s     |\n", located[8], located[9], located[10], located[11], located[12]);
            printf("==============================================\n");
            printf("|��    �u|    %s    |�� �s ��|\n", c[0]);
            printf("|%s     |    %s    |%s     |\n", property[6], c[1], property[12]);
            printf("|%s     |    %s    |%s     |\n", located[7], c[2], located[13]);
            printf("==========    %s    ==========\n", c[3]);
            printf("|�� �� ��|    %s    |�� �� ��|\n", c[4]);
            printf("|%s     |    %s    |%s     |\n", property[5], c[5], property[13]);
            printf("|%s     |    %s    |%s     |\n", located[6], c[6], located[14]);
            printf("==========    %s    ==========\n", c[7]);
            printf("|�� �� ��|    %s    |�F    ��|\n", c[8]);
            printf("|%s     |    %s    |%s     |\n", property[4], c[9], property[14]);
            printf("|%s     |    %s    |%s     |\n", located[5], c[10], located[15]);
            printf("==============================================\n");
            printf("|\033[36m�d���ө�\033[m|���Ƥ���|�U �l ��|��    �B|\033[31m�a���Ȧ�\033[m|\n");
            printf("|%s     |%s     |%s     |%s     |        |\n", property[3], property[2], property[1], property[0]);
            printf("|%s     |%s     |%s     |%s     |%s     |\n", located[4], located[3], located[2], located[1], located[0]);
            printf("==============================================\n");
            usleep(TIME);
        }
    }
    else if (chance == 2)
    {
        for (int i = 0; i < 12; i++)
        {
            c[i] = b[i];
            system("cls");
            printf("==============================================\n");
            printf("|\033[33m��    �|\033[m|�] �� ��|�^ �Y ��|��    �c|\033[33m�R    �B\033[m|\n");
            printf("|%s     |%s     |%s     |%s     |%s     |\n", property[7], property[8], property[9], property[10], property[11]);
            printf("|%s     |%s     |%s     |%s     |%s     |\n", located[8], located[9], located[10], located[11], located[12]);
            printf("==============================================\n");
            printf("|��    �u|    %s    |�� �s ��|\n", c[0]);
            printf("|%s     |    %s    |%s     |\n", property[6], c[1], property[12]);
            printf("|%s     |    %s    |%s     |\n", located[7], c[2], located[13]);
            printf("==========    %s    ==========\n", c[3]);
            printf("|�� �� ��|    %s    |�� �� ��|\n", c[4]);
            printf("|%s     |    %s    |%s     |\n", property[5], c[5], property[13]);
            printf("|%s     |    %s    |%s     |\n", located[6], c[6], located[14]);
            printf("==========    %s    ==========\n", c[7]);
            printf("|�� �� ��|    %s    |�F    ��|\n", c[8]);
            printf("|%s     |    %s    |%s     |\n", property[4], c[9], property[14]);
            printf("|%s     |    %s    |%s     |\n", located[5], c[10], located[15]);
            printf("==============================================\n");
            printf("|\033[36m�d���ө�\033[m|���Ƥ���|�U �l ��|��    �B|\033[31m�a���Ȧ�\033[m|\n");
            printf("|%s     |%s     |%s     |%s     |        |\n", property[3], property[2], property[1], property[0]);
            printf("|%s     |%s     |%s     |%s     |%s     |\n", located[4], located[3], located[2], located[1], located[0]);
            printf("==============================================\n");
            usleep(TIME);
        }
    }
    else if (chance == 3)
    {
        for (int i = 12; i >= 0; i--)
        {
            c[i] = d[i];
            system("cls");
            printf("==============================================\n");
            printf("|\033[33m��    �|\033[m|�] �� ��|�^ �Y ��|��    �c|\033[33m�R    �B\033[m|\n");
            printf("|%s     |%s     |%s     |%s     |%s     |\n", property[7], property[8], property[9], property[10], property[11]);
            printf("|%s     |%s     |%s     |%s     |%s     |\n", located[8], located[9], located[10], located[11], located[12]);
            printf("==============================================\n");
            printf("|��    �u|    %s    |�� �s ��|\n", c[0]);
            printf("|%s     |    %s    |%s     |\n", property[6], c[1], property[12]);
            printf("|%s     |    %s    |%s     |\n", located[7], c[2], located[13]);
            printf("==========    %s   ==========\n", c[3]);
            printf("|�� �� ��|    %s    |�� �� ��|\n", c[4]);
            printf("|%s     |    %s    |%s     |\n", property[5], c[5], property[13]);
            printf("|%s     |    %s    |%s     |\n", located[6], c[6], located[14]);
            printf("==========    %s    ==========\n", c[7]);
            printf("|�� �� ��|    %s    |�F    ��|\n", c[8]);
            printf("|%s     |    %s    |%s     |\n", property[4], c[9], property[14]);
            printf("|%s     |    %s    |%s     |\n", located[5], c[10], located[15]);
            printf("==============================================\n");
            printf("|\033[36m�d���ө�\033[m|���Ƥ���|�U �l ��|��    �B|\033[31m�a���Ȧ�\033[m|\n");
            printf("|%s     |%s     |%s     |%s     |        |\n", property[3], property[2], property[1], property[0]);
            printf("|%s     |%s     |%s     |%s     |%s     |\n", located[4], located[3], located[2], located[1], located[0]);
            printf("==============================================\n");
        }
    }
    else
    {
        system("cls");
        printf("==============================================\n");
        printf("|\033[33m��    �|\033[m|�] �� ��|�^ �Y ��|��    �c|\033[33m�R    �B\033[m|\n");
        printf("|%s     |%s     |%s     |%s     |%s     |\n", property[7], property[8], property[9], property[10], property[11]);
        printf("|%s     |%s     |%s     |%s     |%s     |\n", located[8], located[9], located[10], located[11], located[12]);
        printf("==============================================\n");
        printf("|��    �u|    %s    |�� �s ��|\n", c[0]);
        printf("|%s     |    %s    |%s     |\n", property[6], c[1], property[12]);
        printf("|%s     |    %s    |%s     |\n", located[7], c[2], located[13]);
        printf("==========    %s    ==========\n", c[3]);
        printf("|�� �� ��|    %s    |�� �� ��|\n", c[4]);
        printf("|%s     |    %s    |%s     |\n", property[5], c[5], property[13]);
        printf("|%s     |    %s    |%s     |\n", located[6], c[6], located[14]);
        printf("==========    %s    ==========\n", c[7]);
        printf("|�� �� ��|    %s    |�F    ��|\n", c[8]);
        printf("|%s     |    %s    |%s     |\n", property[4], c[9], property[14]);
        printf("|%s     |    %s    |%s     |\n", located[5], c[10], located[15]);
        printf("==============================================\n");
        printf("|\033[36m�d���ө�\033[m|���Ƥ���|�U �l ��|��    �B|\033[31m�a���Ȧ�\033[m|\n");
        printf("|%s     |%s     |%s     |%s     |        |\n", property[3], property[2], property[1], property[0]);
        printf("|%s     |%s     |%s     |%s     |%s     |\n", located[4], located[3], located[2], located[1], located[0]);
        printf("==============================================\n");
    }
    return 0;
}
