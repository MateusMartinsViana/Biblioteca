#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>
#include <windows.h>
using namespace std;
int main(){
    SetConsoleOutputCP(CP_UTF8);
    FILE *Biblioteca, *BibliotecaAux;
    struct emprestimo {
        char dt_emprestimo[10], dt_devolucao[10], usuario[100];
    } ;
    struct cadastro {
        int cod_catalogacao, num_paginas;
        char area[100], titulo[100], autor[100], editora[100];
        struct emprestimo emp;
    } ;
    struct cadastro cad;

    int opcao, livros_cadastrados, busca, pos, i;
    string continuar;
    bool repetido, encontrado;
    
    i=0;
    livros_cadastrados=0;

    do {
        cout << "MENU DE OPÇÕES DA BIBLIOTECA" << endl;
        cout << "1-Cadastro" << endl;
        cout << "2-Alteração" << endl;
        cout << "3-Exclusão" << endl;
        cout << "4-Empréstimo" << endl;
        cout << "5-Devolução" << endl;
        cout << "6-Consulta de livro" << endl;
        cout << "7-Livros disponíveis" << endl;
        cout << "8-Listagem geral de livros" << endl;
        cout << "9-Sair" << endl;
        cout << "────────────────────────────" << endl;
        cout << "Escolha uma opcão: ";
        cin >> opcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
   
        switch (opcao) {
            case 1:
            Biblioteca = fopen("Biblioteca.dat", "ab+"); 
            if (Biblioteca == NULL)
                cout << "Erro ao abrir o arquivo!";
            else {
                cout << "Deseja iniciar o cadastro do livro? ";
                cin >> continuar;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");

                while (continuar == "Sim" || continuar == "sim" || continuar == "SIM" || continuar == "S" || continuar == "s") {
                    cout << "─────────────── CADASTRO ───────────────" << endl;
                    cout << "Digite o código do livro para cadastro: ";
                    cin >> cad.cod_catalogacao;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    repetido = false;

                    fseek(Biblioteca, 0, SEEK_SET); // vai pro início do arquivo
                    struct cadastro temp; // struct temporária
                    while (!feof(Biblioteca)) {
                        fread(&temp, sizeof(struct cadastro), 1, Biblioteca);
                        if (temp.cod_catalogacao == cad.cod_catalogacao) {
                            repetido = true;
                            cout << "Este livro já está cadastrado!" << endl;
                            cin.get();
                            break;
                        }
                    }

                    if (repetido == false) { 
                        cout << "Área: ";
                        cin.get(cad.area, 99);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Título: ";
                        cin.get(cad.titulo, 99);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Autor(es): ";
                        cin.get(cad.autor, 99);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Editora: ";
                        cin.get(cad.editora, 99);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Nº de páginas: ";
                        cin >> cad.num_paginas;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Livro cadastrado com sucesso!" << endl;  
                        
                        strcpy(cad.emp.dt_emprestimo, "");
                        strcpy(cad.emp.dt_devolucao, "");
                        strcpy(cad.emp.usuario, "");
                        
                        i++;
                        livros_cadastrados++;
                        
                    if (fwrite(&cad, sizeof(struct cadastro), 1, Biblioteca) == 1) { 
                        cout << "Registro gravado com sucesso!";
                        cin.get();       
                    } else {
                        cout << "Erro ao gravar registro!";
                        cin.get();
                    }          
                }    
                system("cls");
                cout << "Deseja cadastrar outro livro? ";
                cin >> continuar;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                }
            }
                fclose(Biblioteca); 

            break;

            case 2:
                do {
                    encontrado = false;
                    cout << "─────────────── ALTERAÇÃO ───────────────" << endl;
                    cout << "Digite o código do livro para alteração: ";
                    cin >> busca;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    Biblioteca = fopen("Biblioteca.dat","rb+");
                    pos = -1;
                    while (!feof(Biblioteca)) {
                        fread (&cad, sizeof(struct cadastro), 1, Biblioteca);
                        pos++;
                        if (busca == cad.cod_catalogacao) {
                            encontrado = true;
                            fseek (Biblioteca, sizeof(struct cadastro)*pos, SEEK_SET); // posiciona o cursor no começo do arquivo 
                            cout << "Área: ";
                            cin.get(cad.area, 99);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Título: ";
                            cin.get(cad.titulo, 99);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Autor(es): ";
                            cin.get(cad.autor, 99);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Editora: ";
                            cin.get(cad.editora, 99);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Nº de páginas: ";
                            cin >> cad.num_paginas;
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Livro alterado com sucesso!" << endl; 
                            fwrite (&cad, sizeof(struct cadastro), 1, Biblioteca);
                            break;
                        } 
                    }
                    if (encontrado == false) {
                        cout << "Livro não encontrado." << endl;
                    }

                    fclose(Biblioteca);
                    cout << "Deseja realizar outra alteração? ";
                    cin >> continuar;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                       
                } while (continuar == "Sim" || continuar == "sim" || continuar == "SIM" || continuar == "S" || continuar == "s");

            break;

            case 3:
                do {
                    cout << "─────────────── EXCLUSÃO ───────────────" << endl;
                    cout << "Digite o código do livro para exclusão: ";
                    cin >> busca;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    BibliotecaAux = fopen ("Biblioteca.aux","wb");
                    Biblioteca = fopen ("Biblioteca.dat","rb");
                    fread (&cad, sizeof(struct cadastro), 1, Biblioteca);
                    while (!feof(Biblioteca)) {
                        if (busca != cad.cod_catalogacao) { // código diferente da busca copia no arquivo auxiliar
                            fwrite (&cad, sizeof(struct cadastro), 1, BibliotecaAux);
                        }
                    fread (&cad, sizeof(struct cadastro), 1, Biblioteca);
                    }

                    fclose (Biblioteca);
                    fclose (BibliotecaAux);
                    remove("Biblioteca.dat"); // remove o arquivo original
                    rename ("Biblioteca.aux","Biblioteca.dat"); // renomeia o arquivo auxiliar para o nome do arquivo original

                    cout << "Livro excluido com sucesso!" << endl;
                    cout << "Deseja realizar outra exclusão? ";
                    cin >> continuar;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");

                } while (continuar == "Sim" || continuar == "sim" || continuar == "SIM" || continuar == "S" || continuar == "s");

            break;

            case 4:
                do {
                    encontrado = false;
                    cout << "─────────────── EMPRÉSTIMO ───────────────" << endl;
                    cout << "Digite o código do livro para empréstimo: ";
                    cin >> busca;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    Biblioteca = fopen ("Biblioteca.dat","rb+");
                    pos = -1;
                    while (!feof(Biblioteca)) {
                        fread (&cad, sizeof(struct cadastro), 1, Biblioteca);
                        pos++;
                        if (busca == cad.cod_catalogacao ) {
                            encontrado = true;
                            if (strcmp(cad.emp.usuario, "") == 0) { // verifica se o campo usuário está vazio
                                fseek (Biblioteca, sizeof(struct cadastro)*pos, SEEK_SET); // posiciona o cursor no começo do arquivo 
                                cout << "Dt. Empréstimo: ";
                                cin.get(cad.emp.dt_emprestimo, 9);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Dt. Devolução: ";
                                cin.get(cad.emp.dt_devolucao, 9);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Usuário: ";
                                cin.get(cad.emp.usuario, 99);
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Empréstimo realizado com sucesso!" << endl;
                                fwrite (&cad, sizeof(struct cadastro), 1, Biblioteca);
                                break;
                            } else {
                                cout << "Livro indisponível para empréstimo." << endl;
                                break;
                            }
                        }
                    }

                    if (encontrado == false) {
                        cout << "Livro não encontrado." << endl;
                    }
                   
                    fclose (Biblioteca);
                    cout << "Deseja realizar outro empréstimo? ";
                    cin >> continuar;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                    
                } while (continuar == "Sim" || continuar == "sim" || continuar == "SIM" || continuar == "S" || continuar == "s");

            break;

            case 5:
                do {
                    encontrado = false;
                    cout << "─────────────── DEVOLUÇÃO ───────────────" << endl;
                    cout << "Digite o código do livro para devolução: ";
                    cin >> busca;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    Biblioteca = fopen ("Biblioteca.dat","rb+");
                    pos = -1;
                    while (!feof(Biblioteca)) {
                        fread (&cad, sizeof(struct cadastro), 1, Biblioteca);
                        pos++;
                        if (busca == cad.cod_catalogacao ) {
                            encontrado = true;
                            if (strcmp(cad.emp.usuario, "") != 0) { // verifica se o campo usuário não esta vazio
                                fseek (Biblioteca, sizeof(struct cadastro)*pos, SEEK_SET); // posiciona o cursor no começo do arquivo  
                                strcpy(cad.emp.dt_emprestimo, ""); // limpa os campos de empréstimo
                                strcpy(cad.emp.dt_devolucao, "");
                                strcpy(cad.emp.usuario, "");
                                cout << "Devolução realizada com sucesso!" << endl;
                                fwrite (&cad, sizeof(struct cadastro), 1, Biblioteca);
                                break;
                            } else {
                                cout << "Livro disponível para empréstimo." << endl; 
                                break;
                            }
                        }
                    }

                    if (encontrado == false) {
                        cout << "Livro não encontrado." << endl;
                    }
                    
                    fclose (Biblioteca);
                    cout << "Deseja realizar outra devolução? ";
                    cin >> continuar;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                    
                } while (continuar == "Sim" || continuar == "sim" || continuar == "SIM" || continuar == "S" || continuar == "s");

            break;

            case 6:
                do {
                    encontrado = false;
                    cout << "─────────── CONSULTA DE LIVRO ──────────" << endl;
                    cout << "Digite o código do livro para consulta: ";
                    cin >> busca;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    Biblioteca = fopen ("Biblioteca.dat","rb");
                    while (!feof(Biblioteca)) {
                        fread(&cad, sizeof(struct cadastro), 1, Biblioteca);
                        if (busca == cad.cod_catalogacao) {
                            encontrado = true;

                            if (strcmp(cad.emp.usuario, "") == 0) { // verifica se o campo usuário está vazio
                                cout << "Status: Disponivel" << endl;
                                cout << "Código de catalogação: " << cad.cod_catalogacao << endl;
                                cout << "Área: " << cad.area << endl;
                                cout << "Título: " << cad.titulo << endl;
                                cout << "Autor(es): " << cad.autor << endl;
                                cout << "Editora: " << cad.editora << endl;
                                cout << "Nº de páginas: " << cad.num_paginas << endl;   
                                break;
                            } else {
                                cout << "Status: Emprestado" << endl;
                                cout << "Usuário: " << cad.emp.usuario << endl;                            
                                cout << "Dt. Empréstimo: " << cad.emp.dt_emprestimo << endl;
                                cout << "Dt. Devolução: " << cad.emp.dt_devolucao << endl;
                                break;
                            }
                        }
                    }
                    
                    if (encontrado == false) {
                        cout << "Livro não encontrado." << endl;
                    }
                    
                    fclose (Biblioteca);
                    cout << "Deseja consultar outro livro? ";
                    cin >> continuar;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                    
                } while (continuar == "Sim" || continuar == "sim" || continuar == "SIM" || continuar == "S" || continuar == "s");

            break;

            case 7:
                cout << "────────── LIVROS DISPONÍVEIS ──────────" << endl;
                Biblioteca = fopen ("Biblioteca.dat","rb");
                
                while (!feof(Biblioteca)) {
                    fread (&cad, sizeof(struct cadastro), 1, Biblioteca);
                    if (strcmp(cad.emp.usuario, "") == 0) { // verifica se o campo usuário está vazio
                                cout << "Status: Disponivel" << endl;
                                cout << "Código de catalogação: " << cad.cod_catalogacao << endl;
                                cout << "Área: " << cad.area << endl;
                                cout << "Título: " << cad.titulo << endl;
                                cout << "Autor(es): " << cad.autor << endl;
                                cout << "Editora: " << cad.editora << endl;
                                cout << "Nº de páginas: " << cad.num_paginas << endl;  
                                cout << "────────────────────────────────────────" << endl;
                            }
                        }

                cin.get();
                system("cls");      
                fclose (Biblioteca);

            break;

            case 8:
                Biblioteca = fopen("Biblioteca.dat", "rb");
                cout << "─────── LISTAGEM GERAL DE LIVROS ───────" << endl;

                fread (&cad, sizeof(struct cadastro), 1, Biblioteca);
                    while (!feof(Biblioteca)) {
                            cout << "Código de catalogação: " << cad.cod_catalogacao << endl;
                            cout << "Área: " << cad.area << endl;
                            cout << "Título: " << cad.titulo << endl;
                            cout << "Autor(es): " << cad.autor << endl;
                            cout << "Editora: " << cad.editora << endl;
                            cout << "Nº de páginas: " << cad.num_paginas << endl;   
                            cout << "────────────────────────────────────────" << endl;  
                            fread (&cad, sizeof(struct cadastro), 1, Biblioteca); 
                    }

                cin.get();
                system("cls");       
                fclose(Biblioteca); 

            break;

            case 9:
                cout << "Saindo do sistema..." << endl;
            break;

            default:
                cout << "Opção inválida! Tente novamente." << endl;
                cin.get();
                system("cls");
            break;

        }
            
    } while (opcao != 9) ; 
}   
