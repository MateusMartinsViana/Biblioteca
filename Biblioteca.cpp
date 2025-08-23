#include <iostream>
#include <windows.h>
using namespace std;
int main(){
    SetConsoleOutputCP(CP_UTF8);
    struct emprestimo {
        string dt_emprestimo, dt_devolucao, usuario;
    } ;
    struct cadastro {
        int cod_catalogacao, num_paginas;
        string area, titulo, autor, editora;
        struct emprestimo emp;
    } ;
    struct cadastro cad[1000];
    
    int opcao, opcao_filtro, livros_cadastrados, cod_emprestimo, cod_devolucao, cod_consulta, i, j;
    string continuar, filtro_area, filtro_autor, filtro_editora;
    bool encontrado, repetido;

    livros_cadastrados = 0;
    i=0;

    do {
        cout << "MENU DE OPÇÕES DA BIBLIOTECA" << endl;
        cout << "1-Cadastro" << endl;
        cout << "2-Empréstimo" << endl;
        cout << "3-Devolução" << endl;
        cout << "4-Consulta de livro" << endl;
        cout << "5-Livros disponíveis" << endl;
        cout << "6-Filtro" << endl;
        cout << "7-Sair" << endl;
        cout << "────────────────────────────────" << endl;
        cout << "Escolha uma opcão: ";
        cin >> opcao;
        cin.ignore();
        system("cls");
   
        switch (opcao) {
            case 1:

            do {
                repetido = false;
                
                cout << "────── CADASTRO ──────" << endl;
                cout << "Código de catalogação: ";
                cin >> cad[i].cod_catalogacao;
                cin.ignore();

                for (j=0; j < livros_cadastrados; j++) {
                    if (cad[i].cod_catalogacao == cad[j].cod_catalogacao) {
                        repetido = true;
                        cout << "Este livro já está cadastrado!" << endl;
                    }
                }

                    if (repetido == false) {
                        cout << "Área: ";
                        getline (cin, cad[i].area);
                        cout << "Título: ";
                        getline (cin, cad[i].titulo);
                        cout << "Autor(es): ";
                        getline (cin, cad[i].autor);
                        cout << "Editora: ";
                        getline (cin, cad[i].editora);
                        cout << "Nº de páginas: ";
                        cin >> cad[i].num_paginas;
                        cin.ignore();
                        cout << "Livro cadastrado com sucesso!" << endl;

                        cad[i].emp.dt_emprestimo = "";
                        cad[i].emp.dt_devolucao = "";
                        cad[i].emp.usuario = "";

                        livros_cadastrados++;
                        i++;
                    }

                system("pause");
                system("cls");
                cout << "Deseja cadastrar outro livro? ";
                getline (cin, continuar);
                system("cls");

            } while (continuar == "Sim" || continuar == "sim" || continuar == "SIM" || continuar == "S" || continuar == "s");

            break;

            case 2:

            do {
                encontrado = false;
                cout << "────── EMPRÉSTIMO ──────" << endl;
                cout << "Digite o codigo do livro a ser emprestado: ";
                cin >> cod_emprestimo;
                cin.ignore();
                
                for (j=0; j < livros_cadastrados; j++) {
                    if (cod_emprestimo == cad[j].cod_catalogacao) {
                        encontrado = true;

                        if (cad[j].emp.usuario == "") {
                            cout << "Dt. Empréstimo: ";
                            getline(cin, cad[j].emp.dt_emprestimo);
                            cout << "Dt. Devolução: ";
                            getline(cin, cad[j].emp.dt_devolucao);
                            cout << "Usuário: ";
                            getline(cin, cad[j].emp.usuario);
                            cout << "Empréstimo registrado com sucesso!" << endl;
                        } else {
                            cout << "Livro indisponível para empréstimo" << endl;
                        }
                        break;
                        }
                    }
            
                    if (encontrado == false) {
                        cout << "Livro não encontrado." << endl;
                    }

                system("pause");
                system("cls");
                cout << "Deseja realizar outro emprestimo? ";
                getline (cin, continuar);
                system("cls");

            } while (continuar == "Sim" || continuar == "sim" || continuar == "SIM" || continuar == "S" || continuar == "s");

            break;

            case 3:
            
            do {
                encontrado = false;
                cout << "────── DEVOLUÇÃO ──────" << endl;
                cout << "Digite o codigo do livro para ser devolvido: ";
                cin >> cod_devolucao;
                cin.ignore();

                for (j=0; j < livros_cadastrados; j++) {
                    if (cod_devolucao == cad[j].cod_catalogacao) {
                        encontrado = true;

                        if (cad[j].emp.usuario != "") {
                        cad[j].emp.dt_emprestimo = "";
                        cad[j].emp.dt_devolucao = "";
                        cad[j].emp.usuario = "";
                        cout << "Devolução realizada com sucesso!" << endl;
                        } else {
                            cout << "Livro disponível para empréstimo." << endl;
                        }
                        break;
                    }
                }
                    if (encontrado == false) {
                        cout << "Livro não encontrado." << endl;
                    }

                system("pause");
                system("cls");
                cout << "Deseja realizar outra devolução? ";
                getline (cin, continuar);
                system("cls");

            } while (continuar == "Sim" || continuar == "sim" || continuar == "SIM" || continuar == "S" || continuar == "s");

                break;

            case 4:

            do {
                encontrado = false;
                cout << "────── CONSULTA DE LIVRO ──────" << endl;
                cout << "Digite o código do livro: ";
                cin >> cod_consulta;
                cin.ignore();

                for (j=0; j < livros_cadastrados; j++) {
                    if (cod_consulta == cad[j].cod_catalogacao) {
                        encontrado = true;

                        if (cad[j].emp.usuario == "") {
                            cout << "Status: Disponivel" << endl;
                            cout << "Código de catalogação: " << cad[j].cod_catalogacao << endl;
                            cout << "Área: " << cad[j].area << endl;
                            cout << "Título: " << cad[j].titulo << endl;
                            cout << "Autor(es): " << cad[j].autor << endl;
                            cout << "Editora: " << cad[j].editora << endl;
                            cout << "Nº de páginas: " << cad[j].num_paginas << endl;
                        } else {
                            cout << "Status: Emprestado" << endl;
                            cout << "Usuário: " << cad[j].emp.usuario << endl;                            
                            cout << "Dt. Empréstimo: " << cad[j].emp.dt_emprestimo << endl;
                            cout << "Dt. Devolução: " << cad[j].emp.dt_devolucao << endl;
                        }
                        break;
                    }
                }
                    if (encontrado == false) {
                        cout << "Livro não encontrado." << endl;
                    }
                system("pause");
                system("cls");
                cout << "Deseja consultar outro livro? ";
                getline (cin, continuar);
                system("cls");

            } while (continuar == "Sim" || continuar == "sim" || continuar == "SIM" || continuar == "S" || continuar == "s");

            break;

            case 5:

            do {
                encontrado = false;
                
                cout << "────── LIVROS DISPONÍVEIS ──────" << endl;
                for (j=0; j < livros_cadastrados; j++) {
                    if (cad[j].emp.usuario == "") {
                        encontrado = true;
                        cout << "Código de catalogação: " << cad[j].cod_catalogacao << endl;
                        cout << "Área: " << cad[j].area << endl;
                        cout << "Título: " << cad[j].titulo << endl;
                        cout << "Autor(es): " << cad[j].autor << endl;
                        cout << "Editora: " << cad[j].editora << endl;
                        cout << "Nº de páginas: " << cad[j].num_paginas << endl;
                        cout << "────────────────────────────────" << endl;
                    }
                }
                    if (encontrado == false) {
                        cout << "Nenhum livro disponivel no momento." << endl;
                    }

                cout << "Deseja listar os livros disponiveis novamente? ";
                getline (cin, continuar);
                system("cls");

            } while (continuar == "Sim" || continuar == "sim" || continuar == "SIM" || continuar == "S" || continuar == "s");

            break;

            case 6:

            do {
                cout << "────── FILTRO ──────" << endl;
                cout << "1-Filtrar por Área" << endl;
                cout << "2-Filtrar por Autor" << endl;
                cout << "3-Filtrar por Editora" << endl;
                cout << "4-Voltar ao Menu Principal" << endl;
                cout << "────────────────────────────────" << endl;
                cout << "Escolha uma opcao: ";
                cin >> opcao_filtro;
                cin.ignore();
                system("cls");

                switch (opcao_filtro) {
                    case 1:
                    do {
                        encontrado = false;
                        cout << "────── FILTRO POR ÁREA ──────" << endl;
                        cout << "Digite a área para a busca: ";
                        getline (cin, filtro_area);
                        system("cls");
                        cout << "RESULTADOS DA BUSCA POR ÁREA" << endl;
                        cout << "─────────────────────────────" << endl;

                        for (j=0; j < livros_cadastrados; j++) {
                            if (filtro_area == cad[j].area) {
                                encontrado = true;
                                cout << "Código de catalogação: " << cad[j].cod_catalogacao << endl;
                                cout << "Área: " << cad[j].area << endl;
                                cout << "Título: " << cad[j].titulo << endl;
                                cout << "Autor(es): " << cad[j].autor << endl;
                                cout << "Editora: " << cad[j].editora << endl;
                                cout << "Nº de páginas: " << cad[j].num_paginas << endl;
                                cout << "─────────────────────────────" << endl;
                            }
                        }
                            if (encontrado == false) {
                                cout << "Nenhum livro encontrado para esta área." << endl;
                            }

                        cout << "Deseja filtrar por outra Area? ";
                        getline (cin, continuar);
                        system("cls");
                        
                    } while (continuar == "Sim" || continuar == "sim" || continuar == "SIM" || continuar == "S" || continuar == "s");

                    break;

                    case 2:
                    
                    do {
                        encontrado = false;

                        cout << "────── FILTRO POR AUTOR ──────" << endl;
                        cout << "Digite o autor para a busca: ";
                        getline (cin, filtro_autor);
                        system("cls");
                        cout << "RESULTADOS DA BUSCA POR AUTOR" << endl;
                        cout << "──────────────────────────────" << endl;
                        
                        for (j=0; j < livros_cadastrados; j++) {
                            if (filtro_autor == cad[j].autor) {
                                encontrado = true;
                                
                                cout << "Código de catalogação: " << cad[j].cod_catalogacao << endl;
                                cout << "Área: " << cad[j].area << endl;
                                cout << "Título: " << cad[j].titulo << endl;
                                cout << "Autor(es): " << cad[j].autor << endl;
                                cout << "Editora: " << cad[j].editora << endl;
                                cout << "Nº de páginas: " << cad[j].num_paginas << endl;
                                cout << "──────────────────────────────" << endl;
                            }
                        }
                            if (encontrado == false) {
                                cout << "Nenhum livro encontrado para este autor." << endl;
                            }

                        cout << "Deseja filtrar por outro autor? ";
                        getline (cin, continuar);
                        system("cls");

                    } while (continuar == "Sim" || continuar == "sim" || continuar == "SIM" || continuar == "S" || continuar == "s");

                    break;

                    case 3:

                    do {
                        encontrado = false;

                        cout << "────── FILTRO POR EDITORA ──────" << endl;
                        cout << "Digite a editora para a busca: ";
                        getline (cin, filtro_editora);
                        system("cls");
                        cout << "RESULTADOS DA BUSCA POR EDITORA" << endl;
                        cout << "────────────────────────────────" << endl;
                        
                        for (j=0; j < livros_cadastrados; j++) {
                            if (filtro_editora == cad[j].editora) {
                                encontrado = true;
                                
                                cout << "Código de catalogação: " << cad[j].cod_catalogacao << endl;
                                cout << "Área: " << cad[j].area << endl;
                                cout << "Título: " << cad[j].titulo << endl;
                                cout << "Autor(es): " << cad[j].autor << endl;
                                cout << "Editora: " << cad[j].editora << endl;
                                cout << "Nº de páginas: " << cad[j].num_paginas << endl;
                                cout << "────────────────────────────────" << endl;
                            }
                        }
                            if (encontrado == false) {
                                cout << "Nenhum livro encontrado para este autor." << endl;
                            }

                        cout << "Deseja filtrar por outra editora? ";
                        getline (cin, continuar);
                        system("cls");

                    } while (continuar == "Sim" || continuar == "sim" || continuar == "SIM" || continuar == "S" || continuar == "s");

                    break;
                } 

            } while (opcao_filtro != 4) ;

            break;

            case 7:
                cout << "Saindo do sistema..." << endl;
            break;

            default:
                cout << "Opção inválida! Tente novamente." << endl;
                system("pause");
                system("cls");
            break;
        }

    } while (opcao != 7) ;
}