
class TextQuery
{
	public:
	
	private:
		void store_file(std::ifstream&);
		void build_map();
		
 		std::vector<std::string> lines_of_text;
		std::map< std::string, std::set<line_no> > word_map;
}