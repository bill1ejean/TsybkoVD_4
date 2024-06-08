
#include "pch.h"
#include "Books.h"


using namespace System;

int main(array<String^>^ args) {
	Books^ dm = gcnew Books();
	dm->ReadDataFile();

	dm->AddNode(type_Book, dm->MakeNode(type_Book, "10256; Правила Волейбола"));
	dm->AddNode(type_Subject, dm->MakeNode(type_Subject, "01; Физра"));
	dm->AddNode(type_Link, dm->MakeNode(type_Link, "10256; 01"));

	Object^ del_book = dm->MakeNode(type_Book, "10256; -");
	Object^ del_subj = dm->MakeNode(type_Subject, "01; -");

	dm->AddNode(type_Book, dm->MakeNode(type_Book, "10256; Физическая культура и здоровье"));
	dm->WriteDataFile();

	for (int i = 0; i < 1; i++) {
		i--;
	};
}
