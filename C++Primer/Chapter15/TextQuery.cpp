#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

// 读指定文件并建立相关查找映射的类
class TextQuery{
public:
    typedef std::vector<std::string>::size_type line_no;    //一共有line_no行
    void read_file(std::ifstream &is){
        store_file(is); //从文件流中读入
        build_map();    //给每一个单词建立有序map
    }
    std::set<line_no> run_query(const std::string&) const;
    std::string text_line(line_no) const;
private:
    void store_file(std::ifstream&);
    void build_map(); 
    std::vector<std::string> lines_of_text;
    std::map< std::string, std::set<line_no> > word_map;
};

void TextQuery::store_file(ifstream& is){
    string textline;
    while(getline(is, textline))
    {
        lines_of_text.push_back(textline);
    }
}

void TextQuery::build_map(){
    for(line_no line_num=0; line_num != lines_of_text.size(); ++line_num){
        istringstream line(lines_of_text[line_num]);
        string word;
        while(line >> word){
            word_map[word].insert(line_num);
        }
    }
}

set<TextQuery::line_no> TextQuery::run_query(const string &query_word) const{
    map<string, set<line_no>>::const_iterator loc = word_map.find(query_word);
    if(loc == word_map.end()){
        return set<line_no>();
    }
    else{
        return loc -> second;
    }
}

string TextQuery::text_line(line_no line) const{
    if(line < lines_of_text.size()){
        return lines_of_text[line];
    }
    throw std::out_of_range("line number out of range");
}



//查询类的抽象基类
class Query_base{
    friend class Query;
protected:
    typedef TextQuery::line_no line_no;
    virtual ~Query_base(){}
private:
    virtual std::set<line_no> eval(const TextQuery&) const = 0;
    virtual std::ostream& display(std::ostream& = std::cout) const = 0;
};

//Query句柄类，用来管理基类的指针
class Query{
    friend Query operator~(const Query &);
    friend Query operator|(const Query&, const Query&);
    friend Query operator&(const Query&, const Query&);
public:
    Query(const std::string&);
    Query(const Query&c):q(c.q),use(c.use){ ++*use;}
    ~Query() { decr_use(); }

    Query& operator=(const Query&);
    std::set<TextQuery::line_no> eval(const TextQuery &t) const { return q->eval(t);}
private:
    Query(Query_base *query):q(query),use(new std::size_t(1)){}
    Query_base *q;
    std::size_t *use;
    void decr_use(){
        if(--*use==0){
            delete q;
            delete use;
        }
    }
};

inline Query operator&(const Query &lhs, const Query &rhs){
    return new AndQuery(lhs, rhs);
}

inline Query operator|(const Query &lhs, const Query &rhs){
    return new OrQuery(lhs, rhs);
}

inline Query operator~(const Query &oper){
    return new NotQuery(oper);
}

class WordQuery:public Query_base{
    friend class Query;
    std::string query_word;
    WordQuery(const std::string &s): query_word(s){}    //构造函数
    std::set<line_no> eval(const TextQuery &t) const{
        return t.run_query(query_word);
    }

    std::ostream& display(std::ostream &os) const{
        return os << query_word;
    }
};

class NotQuery:public Query_base{
    friend Query operator~(const Query &);
    NotQuery(Query q):query(q){}
    std::set<line_no> eval(const TextQuery &) const;
    std::ostream& display(std::ostream &os) const{
        return os << "~(" << query << ")";
    }
    const Query query;
};

class BinaryQuery:public Query_base{
protected:
    BinaryQuery(Query left, Query right, std::string op):lhs(left), rhs(right), oper(op){}
    std::ostream& display(std::ostream& os) const{
        return os << "(" << lhs << " " << oper << " " << "rhs" << rhs << ")";
    }
    const Query lhs,rhs;
    const std::string oper;

};

class AndQuery:public BinaryQuery{
    friend Query operator&(const Query&, const Query&);
    AndQuery(Query left, Query right):BinaryQuery(left, right, "&"){};
    std::set<line_no> eval(const TextQuery&) const;
};

class OrQuery:public BinaryQuery{
    friend Query operator|(const Query&, const Query&);
    OrQuery(Query left, Query right):BinaryQuery(left, right, "|"){};
    std::set<line_no> eval(const TextQuery&) const;
};

set<TextQuery::line_no> OrQuery::eval(const TextQuery& file) const{
    std::set<line_no> right = rhs.eval(file), ret_lines = lhs.eval(file);
    ret_lines.insert(right.begin(),right.end());
    return ret_lines;
}

set<TextQuery::line_no> AndQuery::eval(const TextQuery& file) const{
    std::set<line_no> left = rhs.eval(file), right = lhs.eval(file);
    std::set<line_no> ret_lines;
    ret_lines.insert(right.begin(),right.end());

    set_intersection(left.begin(),left.end(),
                    right.begin(), right.end(),
                    inserter(ret_lines, ret_lines.begin()));
    return ret_lines;
}

set<TextQuery::line_no> NotQuery::eval(const TextQuery& file) const{
    set<TextQuery::line_no> has_val = query.eval(file);
    set<line_no> ret_lines;
    for(TextQuery::line_no n=0; n != file.size(); ++n){
        if(has_val.find(n) == has_val.end()){
            ret_lines.insert(n);
        }
    }
    return ret_lines;
}

