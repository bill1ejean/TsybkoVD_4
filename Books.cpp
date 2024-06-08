#include "Books.h"
#include "pch.h"
using namespace System;
using namespace System::IO;

Books::Books() {
    this->fileLinksPath = gcnew String("./Links.txt");
    this->fileBooksPath = gcnew String("./Books.txt");
    this->fileSubjectsPath = gcnew String("./Subjects.txt");

    this->listLinks = gcnew List<Object^>();
    this->listBooks = gcnew List<Object^>();
    this->listSubjects = gcnew List<Object^>();

     Console::WriteLine("Создан объект класса "); 
}

void Books::ReadDataFile() {
        try {
                StreamReader ^ sr = gcnew StreamReader(this->fileLinksPath);
                String ^ line;
                while ((line = sr->ReadLine()) != nullptr) {
                        this->AddNode(type_Link, this->MakeNode(type_Link, line));
           
       }
                sr->Close();
                Console::WriteLine("Прочитан файл Links.txt");
       
   }
        catch (Exception^ e) {
                Console::WriteLine("Ошибка, невозможно прочитать Links.txt\n" + e);
                Environment::Exit(1);
       
   }
        try {
                StreamReader ^ sr = gcnew StreamReader(this->fileBooksPath);
                String ^ line;
                while ((line = sr->ReadLine()) != nullptr) {
                        this->AddNode(type_Book, this->MakeNode(type_Book, line));
           
       }
                sr->Close();
                Console::WriteLine("Прочитан файл Books.txt");
       
   }
        catch (Exception^ e) {
                Console::WriteLine("Ошибка, невозможно прочитать Books.txt\n" + e);
                Environment::Exit(1);
       
   }
        try {
                StreamReader ^ sr = gcnew StreamReader(this->fileSubjectsPath);
                String ^ line;
                while ((line = sr->ReadLine()) != nullptr) {
                        this->AddNode(type_Subject, this->MakeNode(type_Subject, line));
           
       }
                sr->Close();
                Console::WriteLine("Прочитан файл Subjects.txt");
       
   }
        catch (Exception^ e) {
                Console::WriteLine("Ошибка, невозможно прочитать Subjects.txt\n" + e);
                Environment::Exit(1);
       
   }
   
}

 void Books::WriteDataFile() {
         StreamWriter ^ sw = nullptr;
         sw = File::CreateText(this->fileLinksPath);
         for each (Link ^ link in (this->listLinks)) {
                String ^ text = String::Format("{0}; {1}", link->bookid, link->subjid);
                sw->WriteLine(text);
        
    }
         sw->Close();
         Console::WriteLine("Файл Links.txt обновлен новыми данными");
         sw = File::CreateText(this->fileBooksPath);
         for each (Book ^ book in (this->listBooks)) {
                 String ^ text = String::Format("{0}; {1}", book->bookid, book->nameofbook);
                 sw->WriteLine(text);
        
    }
         sw->Close();
         Console::WriteLine("Файл Books.txt обновлен новыми данными");
         sw = File::CreateText(this->fileSubjectsPath);
         for each (Subject ^ subject in (this->listSubjects)) {
                 String ^ text = String::Format("{0}; {1}", subject->subjid, subject->nameofsubj);
                 sw->WriteLine(text);
        
    }
         sw->Close();
         Console::WriteLine("Файл Books.txt обновлен новыми данными");
    
}
  Object^ Books::MakeNode(DataType type, String^ line) {
          Object ^ node = nullptr;
          array<String^> ^ data = line->Split(';');
          switch (type) {
          case type_Link:
                  if (data->Length == 2) {
                          Link ^ temp = gcnew Link();
                          temp->bookid = data[0]->Trim();
                          temp->subjid = data[1]->Trim();
                          node = temp;
             
         }
                  break;
          case type_Book:
                  if (data->Length == 2) {
                         Book ^ temp = gcnew Book();
                         temp->bookid = data[0]->Trim();
                         temp->nameofbook = data[1]->Trim();
                         node = temp;
             
         }
                  break;
          case type_Subject:
                   if (data->Length == 2) {
                          Subject ^ temp = gcnew Subject();
                          temp->subjid = data[0]->Trim();
                          temp->nameofsubj = data[1]->Trim();
                          node = temp;
             
         }
                   break;
          default:
                  Console::WriteLine("Ошибка, выбран некорректный формат данных");
                  break;
         
     }
          return node;
     
 }
 void Books::AddNode(DataType type, Object^ node) {
           switch (type) {
           case type_Link:
                   this->listLinks->Add(node);
                   Console::WriteLine("В список связей добавлена запись");
                   break;
           case type_Book:
                   this->listBooks->Add(node);
                   Console::WriteLine("В список книг добавлена запись");
                   break;
           case type_Subject:
                   this->listSubjects->Add(node);
                   Console::WriteLine("В список дисциплин добавлена запись");
                   break;
           default:
                     Console::WriteLine("Ошибка, выбран некорректный формат данных");
                     break;
            
      }
      
  }
 void Books::DeleteNode(DataType type, Object ^ node) {
          Link ^ t_link = nullptr;
          Book ^ t_book = nullptr;
          Subject ^ t_subj = nullptr;
          int del_count = 0;
          switch (type) {
          case type_Link:
                  t_link = dynamic_cast <Link^> (node);
                  for (int i = 0; i < this->listLinks->Count; i++) {
                          Link ^ link = dynamic_cast <Link^> (this->listLinks[i]);
                          if (t_link->bookid == link->bookid && t_link->subjid == link->subjid) {
                                  this->listLinks->RemoveAt(i);
                                  break;
                 
             }
             
         }
                  Console::WriteLine("Из списка связей удалена запись");
                  break;
          case type_Book:
                  t_book = dynamic_cast<Book^>(node);
                  for (int i = 0; i < this->listBooks->Count; i++) {
                          Book ^ book = dynamic_cast <Book^> (this->listBooks[i]);
                          if (t_book->bookid == book->bookid) {
                                  for (int j = 0; j < this->listLinks->Count; j++) {
                                          Link ^ link = dynamic_cast <Link^> (this->listLinks[j]);
                                          if (link->bookid == t_book->bookid) {
                                                  this->listLinks->RemoveAt(j);
                                                  del_count++;
                         
                     }
                     
                 }
                                  this->listBooks->RemoveAt(i);
                                  break;
                 
             }
             
         }
                  Console::WriteLine("Из списка книг удалена запись");
                  if (del_count > 0) {
                          Console::WriteLine("Вслед удалено " + del_count + " записей из списка связей");
             
         }
                  break;
          case type_Subject:
                   t_subj = dynamic_cast<Subject^>(node);
                   for (int i = 0; i < this->listSubjects->Count; i++) {
                          Subject ^ subj = dynamic_cast <Subject^> (this->listSubjects[i]);
                          if (t_subj->subjid == subj->subjid) {
                                  for (int j = 0; j < this->listLinks->Count; j++) {
                                          Link ^ link = dynamic_cast <Link^> (this->listLinks[j]);
                                          if (link->subjid == t_subj->subjid) {
                                                  this->listLinks->RemoveAt(j);
                                                  del_count++;
                         
                     }
                     
                 }
                                  this->listSubjects->RemoveAt(i);
                                  break;
                 
             }
             
         }
                  Console::WriteLine("Из списка дисциплин удалена запись");
                  if (del_count > 0) {
                          Console::WriteLine("Вслед удалено " + del_count + " записей из списка связей");
             
         }
                 break;
          default:
                   Console::WriteLine("Ошибка, выбран некорректный формат данных");
                   break;
          
     }
     
 }
  List<Object^> ^ Books::FindNode(DataType type, String ^ line) {
          int find_count = 0;
          List<Object^> ^ list = gcnew List<Object^>();
          switch (type) {
          case type_Link:
                  for each (Link ^ link in (this->listLinks)) {
                          if (link->bookid->Contains(line) || link->subjid->Contains(line)) {
                                  list->Add(link);
                 
             }
             
         }
                  break;
          case type_Book:
                  for each (Book ^ book in (this->listBooks)) {
                          if (book->bookid->Contains(line) || book->nameofbook->Contains(line)) {
                                   list->Add(book);
                  
             }
             
         }
                  break;
          case type_Subject:
                  for each (Subject ^ subj in (this->listSubjects)) {
                          if (subj->subjid->Contains(line) || subj->nameofsubj->Contains(line)) {
                                  list->Add(subj);
                 
             }
             
         }
                  break;
          default:
                  Console::WriteLine("Ошибка, выбран некорректный формат данных");
                  break;
         
     }
          Console::WriteLine("Найдено " + find_count + " записей по заданной строке");
          return list;
     
 }