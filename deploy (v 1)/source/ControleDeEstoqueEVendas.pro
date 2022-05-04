QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bd_brinde.cpp \
    bd_cliente.cpp \
    bd_esmalte.cpp \
    bd_relatorios.cpp \
    bd_roupa.cpp \
    bd_venda.cpp \
    bd_vendedor.cpp \
    fm_carregando.cpp \
    fm_dados.cpp \
    fm_estoque_esmalte.cpp \
    fm_estoque_roupa.cpp \
    fm_gestao_brinde.cpp \
    fm_gestao_clientes.cpp \
    fm_gestao_esmalte.cpp \
    fm_gestao_roupa.cpp \
    fm_gestao_vendedores.cpp \
    fm_login.cpp \
    fm_menu.cpp \
    fm_novavenda.cpp \
    fm_novavenda_brinde.cpp \
    fm_novavenda_cadastrocliente.cpp \
    fm_novavenda_editar.cpp \
    fm_novavenda_finalizar.cpp \
    fm_novavenda_pesquisar.cpp \
    fm_relatorio_comodato.cpp \
    fm_roupanovavenda.cpp \
    fm_roupanovavenda_editar.cpp \
    fm_roupanovavenda_finalizar.cpp \
    fm_roupanovavenda_pesquisar.cpp \
    fm_transacao_cliente.cpp \
    fm_transacao_vendedor.cpp \
    gl_funcao.cpp \
    main.cpp \
    obj_brinde.cpp \
    obj_cep.cpp \
    obj_cliente.cpp \
    obj_cnpj.cpp \
    obj_dadoscomodato.cpp \
    obj_dadosesmalte.cpp \
    obj_dadosvendedor.cpp \
    obj_esmalte.cpp \
    obj_pessoa.cpp \
    obj_roupa.cpp \
    obj_telefone.cpp \
    obj_vendedor.cpp

HEADERS += \
    bd.h \
    bd_brinde.h \
    bd_cliente.h \
    bd_esmalte.h \
    bd_relatorios.h \
    bd_roupa.h \
    bd_venda.h \
    bd_vendedor.h \
    fm_carregando.h \
    fm_dados.h \
    fm_estoque_esmalte.h \
    fm_estoque_roupa.h \
    fm_gestao_brinde.h \
    fm_gestao_clientes.h \
    fm_gestao_esmalte.h \
    fm_gestao_roupa.h \
    fm_gestao_vendedores.h \
    fm_login.h \
    fm_menu.h \
    fm_novavenda.h \
    fm_novavenda_brinde.h \
    fm_novavenda_cadastrocliente.h \
    fm_novavenda_editar.h \
    fm_novavenda_finalizar.h \
    fm_novavenda_pesquisar.h \
    fm_relatorio_comodato.h \
    fm_roupanovavenda.h \
    fm_roupanovavenda_editar.h \
    fm_roupanovavenda_finalizar.h \
    fm_roupanovavenda_pesquisar.h \
    fm_transacao_cliente.h \
    fm_transacao_vendedor.h \
    gl_ed.h \
    gl_funcao.h \
    gl_variavel.h \
    obj_brinde.h \
    obj_cep.h \
    obj_cliente.h \
    obj_cnpj.h \
    obj_dadoscomodato.h \
    obj_dadosesmalte.h \
    obj_dadosvendedor.h \
    obj_esmalte.h \
    obj_pessoa.h \
    obj_roupa.h \
    obj_telefone.h \
    obj_vendedor.h

FORMS += \
    fm_carregando.ui \
    fm_dados.ui \
    fm_estoque_esmalte.ui \
    fm_estoque_roupa.ui \
    fm_gestao_brinde.ui \
    fm_gestao_clientes.ui \
    fm_gestao_esmalte.ui \
    fm_gestao_roupa.ui \
    fm_gestao_vendedores.ui \
    fm_login.ui \
    fm_menu.ui \
    fm_novavenda.ui \
    fm_novavenda_brinde.ui \
    fm_novavenda_cadastrocliente.ui \
    fm_novavenda_editar.ui \
    fm_novavenda_finalizar.ui \
    fm_novavenda_pesquisar.ui \
    fm_relatorio_comodato.ui \
    fm_roupanovavenda.ui \
    fm_roupanovavenda_editar.ui \
    fm_roupanovavenda_finalizar.ui \
    fm_roupanovavenda_pesquisar.ui \
    fm_transacao_cliente.ui \
    fm_transacao_vendedor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
