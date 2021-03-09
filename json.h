#ifndef _QLSV_H_
#define _QLSV_H_
#endif 

using namespace std;
//------------------DATA---------------------------

//----------------PROTOTYPES------------------------
void convert_to_json(string &tmp,const sinhvien st);
void convert_from_json(sinhvien &st,string s);
void readFile();
void writeFile(sinhvien sv);
void writeFileAll(dataRoot root);
//----------------FUNCTIONS-------------------------
void convert_to_json(string &tmp,const sinhvien st)
{
	string diem = ftos(st.diem);
	string gt = (st.gioiTinh==0?"NU":"NAM");
	tmp = "{\"ID\":\""+st.maSV+"\",\"class\":\""+st.maLop+"\",";
	tmp+="\"date\":\""+st.ngaySinh+"\",\"mark\":"+diem+",\"name\":";
	tmp+="\""+st.hoTen+"\",\"sex\":\""+gt+"\"}";
}
void convert_from_json(sinhvien &st,string tmp)
{	
	int j=tmp.find("ID");
	int k = tmp.find(',',j);
	string id;
	for (int iter =j+5;iter<k-1;iter++)
		id+=tmp[iter];
	st.maSV =id;
	
	
	j=tmp.find("class");
	k = tmp.find(',',j);
	string classes;
	for (int iter =j+8;iter<k-1;iter++)
		classes+=tmp[iter];
	st.maLop=classes;
	
	
	j = tmp.find("date");
	k = tmp.find(',',j);
	string date;
	for (int iter =j+7;iter<k-1;iter++)
		date+=tmp[iter];
	st.ngaySinh =date;
	
	j= tmp.find("mark");
	k = tmp.find(',',j);
	string mark="";
	for (int iter =j+6;iter<k;iter++)
		mark +=tmp[iter];
	//
	try {
    	st.diem = convert_to_float(mark);
  	}
  	catch (const std::invalid_argument& ia) {
	 //do nothing
  }
		
	j= tmp.find("name");
	k = tmp.find(',',j);
	string name;
	for (int iter =j+7;iter<k-1;iter++)
		name +=tmp[iter];
	st.hoTen = name;
	
	j = tmp.find("sex");
	k= tmp.length();
	string sex;
	for (int iter = j+6;iter < k-2;iter++)
		sex+=tmp[iter];
	st.gioiTinh = (sex=="NAM"?1:0);
	
}
void readFile()
{
	ifstream fi;

	fi.open(FILEIN,ios::in);
	sinhvien tmp;
	char s[200];
	//fi.getline(s,200);
	dataSinhVien = NULL;
	while (!fi.eof())
	{
		fi.getline(s,200);
		convert_from_json(tmp,string(s));
		//cout<<s;
		if (strlen(s)>50)
		addSinhVien(tmp,&dataSinhVien);
	}
	fi.close();
}

void writeFile(sinhvien sv)
{
	ofstream fo;
	fo.open(FILEIN, ios::app);
	string j;
	convert_to_json(j,sv);
	fo<<j<<endl;
	fo.close();
}
void writeFileAll(dataRoot root)
{
	ofstream fo;
	string j;
	fo.open(FILEIN, ios::out);
	fo.clear();
	for (cauTruc *i= root;i!= NULL;i= i->next)
	{
		convert_to_json(j,i->data);
		fo<<j<<endl;
	}	
	fo.close();
}
