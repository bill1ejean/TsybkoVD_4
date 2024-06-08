#pragma once
using namespace System;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Collections::Generic;

enum DataType {
	type_Link = 0,
	type_Book = 1,
	type_Subject = 2
};
ref struct Link {
	String^ bookid;
	String^ subjid;
};
ref struct Book {
	String^ bookid;
	String^ nameofbook;

};
ref struct Subject {
	String^ subjid;
	String^ nameofsubj;
};
ref class Books {
private:
	String^ fileLinksPath;
	String^ fileBooksPath;
	String^ fileSubjectsPath;
	List<Object^>^ listLinks;
	List<Object^>^ listBooks;
	List<Object^>^ listSubjects;
public:
	Books();	
	void ReadDataFile();
	void WriteDataFile();
	Object^ MakeNode(DataType, String^);
	void AddNode(DataType, Object^);
	void DeleteNode(DataType, Object^);
	List<Object^>^ FindNode(DataType, String^);

};
