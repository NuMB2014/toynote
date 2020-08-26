/*!
 * \file
 * \brief Файл реализации класса EditNoteDialog.
 * \author Кирилл Пушкарёв
 * \date 2017
 */
#include "editnotedialog.hpp"
// Заголовочный файл UI-класса, сгенерированного на основе editnotedialog.ui
#include "ui_editnotedialog.h"
#include <QMessageBox>
#include "config.hpp"
#include "note.hpp"

/*!
* Конструирует объект класса с родительским объектом \a parent.
* Параметр \p parent имеет значение по умолчанию 0. Указывать родительский
* объект нужно, например чтобы дочерний объект был автоматически удалён
* при удалении родительского. Для EditNoteDialog родителем будет
* окно более высокого уровня, например главное.
*/
EditNoteDialog::EditNoteDialog(QWidget *parent) :
    QDialog(parent), // Передаём parent конструктору базового класса
    mUi(new Ui::EditNoteDialog) // Создаём объект Ui::EditNoteDialog
{
    // Отображаем GUI, сгенерированный из файла editnotedialog.ui, в данном окне
    mUi->setupUi(this);
}

/*!
* Отвечает за уничтожение объектов EditNoteDialog. Сюда можно поместить
* функции, которые надо выполнить перед уничтожением (например, закрыть
* какие-либо файлы или освободить память).
*/
EditNoteDialog::~EditNoteDialog()
{
    // Удаляем объект Ui::EditNoteDialog
    delete mUi;
}

Note *EditNoteDialog::note() const
{
    return mNote;
}

void EditNoteDialog::setNote(Note *note)
{
    mNote = note;
    mUi->titleEdit->setText(note->title());
    mUi->plainTextEdit->setPlainText(note->text());
}
/*!
 * Этот метод вызывается, когда пользователь подтверждает диалог, например
 * нажатием кнопки «OK». Метод изначально определён в базовом классе QDialog,
 * а здесь он переопределяется, то есть при вызове метода accept() у объекта
 * EditNoteDialog будет выполняться этот код, а не тот, что есть в классе
 * QDialog.
 *
 * Метод отвечает за обработку введённых пользователем в диалоге данных.
 * Он считывает данные из полей диалога и записывает их в соответствующие
 * атрибуты редактируемой заметки.
 */
void EditNoteDialog::accept()
{
    if (mUi->titleEdit->text().isEmpty() || mUi->plainTextEdit->toPlainText().isEmpty()){
        QMessageBox::warning(this, tr(Config::applicationName), tr("Text or title is empty in your note. \nProgram can't save this.\nPlease fill all rows."));
    }
    else {
        mNote->setTitle(mUi->titleEdit->text());
        mNote->setText(mUi->plainTextEdit->toPlainText());
        QDialog::accept();
    }
}

QString EditNoteDialog::text(){
    return mUi->plainTextEdit->toPlainText();
}

QString EditNoteDialog::title(){
    return mUi->titleEdit->text();
}
