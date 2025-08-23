#include <iostream>
#include <cstdio>
#include <limits>
#include <windows.h>
using namespace std;
int main(){
    SetConsoleOutputCP(CP_UTF8);
    FILE *Biblioteca;
    struct emprestimo {
        char dt_emprestimo[10], dt_devolucao[10], usuario[100];
    } ;
    struct cadastro {
        int cod_catalogacao, num_paginas;
        char area[100], titulo[100], autor[100], editora[100];
        struct emprestimo emp;
    } ;
    struct cadastro cad;

    int opcao;
    char continuar;
    bool repetido;

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
        cout << "────────────────────────────────" << endl;
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
                cout << "Deseja iniciar o cadastro do livro (S/N): ";
                cin >> continuar;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");

                while (continuar == 'S') {
                    cout << "────── CADASTRO ──────" << endl;
                    cout << "Código de catalogação: ";
                    cin >> cad.cod_catalogacao;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    repetido = false;

                    fseek(Biblioteca, 0, SEEK_SET); // vai pro início do arquivo
                    struct cadastro temp;
                    while (fread(&temp, sizeof(struct cadastro), 1, Biblioteca) == 1) {
                        if (temp.cod_catalogacao == cad.cod_catalogacao) {
                            repetido = true;
                            cout << "Este livro já está cadastrado!" << endl;
                            cin.get();
                            break;
                        }
                    }
                    if (!repetido) { 
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
                        
                    if (fwrite(&cad, sizeof(struct cadastro), 1, Biblioteca) == 1) { 
                        cout << "Registro gravado com sucesso!";
                        cin.get();       
                    } else {
                        cout << "Erro ao gravar registro!";
                        cin.get();
                    }          
                }    
                system("cls");
                cout << "Deseja cadastrar outro livro (S/N): ";
                cin >> continuar;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
                }
            }
                fclose(Biblioteca); 

            break;

            case 8:
                Biblioteca = fopen("Biblioteca.dat", "rb");
                cout << "────── LISTAGEM GERAL DE LIVROS ──────" << endl;

                fread (&cad, sizeof(struct cadastro), 1, Biblioteca);
                    while (!feof(Biblioteca)) {
                            cout << "Código de catalogação: " << cad.cod_catalogacao << endl;
                            cout << "Área: " << cad.area << endl;
                            cout << "Título: " << cad.titulo << endl;
                            cout << "Autor(es): " << cad.autor << endl;
                            cout << "Editora: " << cad.editora << endl;
                            cout << "Nº de páginas: " << cad.num_paginas << endl;   
                            cout << "────────────────────────────────" << endl;  
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
