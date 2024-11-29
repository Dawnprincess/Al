//哈夫曼编码
//输入: 一个文件
//输出: 编码后的压缩文件
#include "../File.hpp"
#include "../TestData.hpp"
#include "../TimeTracker.hpp"
#include <queue>
#include <bitset>
struct HuffmanNode{
    HuffmanNode *left;
    HuffmanNode *right;
    int freq;
    char ch;
    HuffmanNode(char character, int frequency) : ch(character), freq(frequency), left(nullptr), right(nullptr) {}
};
struct Compare{
    bool operator()(HuffmanNode *left,HuffmanNode *right){
        return left->freq > right->freq;
    }
};

//读取文件内容，返回unodered_map,索引表示字符，值表示频率
unordered_map<char ,int>getCharFrequency(const string& filename){
    ifstream file(filename);
    unordered_map<char, int> freq;
    char ch;
    while(file.get(ch)){
        freq[ch]++;
    }
    return freq;
}

//生成哈夫曼树
HuffmanNode *BuildHuffmanTree(const unordered_map<char, int> &freq){
    //生成最小堆，比较的算法为Compare,左子树小于右子树
    priority_queue<HuffmanNode *, vector<HuffmanNode*>,Compare> min_heap;

    //auto自动分辨pair类型，引用freq的元素，并自动进行遍历
    for (const auto&pair : freq){
        min_heap.push(new HuffmanNode(pair.first,pair.second));
    }

    //构建哈夫曼树，非叶子节点的char用\0代替,最小fre合并
    while(min_heap.size() > 1){
        HuffmanNode* left = min_heap.top();min_heap.pop();
        HuffmanNode* right = min_heap.top();min_heap.pop();

        HuffmanNode* newNode = new HuffmanNode('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;
    
        min_heap.push(newNode);
    }

    return min_heap.top();
}

//生成哈夫曼编码,code记录当前分支的编码，codes存储已经编码过的字符
void generateHuffmancode(HuffmanNode *root,const string& code,unordered_map<char,string>& codes){
    //如果root指向空，结束
    if(!root) return;

    //如果是叶子结点
    if(!root->left && !root->right){
        codes[root->ch] = code;
        return;
    }
    //向左递归，加0
    generateHuffmancode(root->left,code + "0", codes);
    generateHuffmancode(root->right, code + "1", codes);
}
//定长编码的实现，用于与哈夫曼编码对比
void generateFixedlengthcode(unordered_map<char, string> &codes,unordered_map<char, int> &fre){
    //计算字符种类数量
    int charNum = fre.size();
    //由种类数量计算最短编码长度
    int codeLength = ceil(log2(charNum));
    //生成固定长度编码,从00...00开始，到最后一个字符结束
    //用i记录当前编码大小,转换为二进制字符串并填充后，放入codes中
    int i = 0;  // 用来记录编码的索引
    for (const auto &entry : fre) {
        // 将 i 转换为固定长度32位二进制字符串
        bitset<32> binary(i);
        //提取前codeLength位
        string code = binary.to_string().substr(32 - codeLength);
        
        // 将编码存入 codes 中
        codes[entry.first] = code;
        
        // 增加 i 以生成下一个编码
        ++i;
    }
    // 输出固定长度编码表
    for (const auto&pair : codes){
        cout << pair.first << " : " << pair.second << endl;
    }
}
//将inputfile文件编码为outputfile文件,code为哈夫曼编码
void encodeFile(const string& inputfile,const string& outputfile,const unordered_map<char, string>& code){
    ifstream infile(inputfile);
    ofstream outfile(outputfile,ios::binary);
    char ch;
    string encodedStr;
    //显示哈夫曼编码表
    
    /*for (const auto&pair : code){
        cout << pair.first << " : " << pair.second << endl;
    }*/
    //encodedStr为编码后的字符串,用Validlength记录有效编码长度
    int Validlength = 0;
    while(infile.get(ch)){
        encodedStr += code.at(ch);
        Validlength += code.at(ch).length();
    }
    
    //显示编码
    cout << "Encoded String: " << encodedStr << endl;
    
    // 将有效位数写入文件（例如，写入前4个字节来存储有效位数）
    outfile.write(reinterpret_cast<char*>(&Validlength), sizeof(Validlength));
    // 将编码转换为字节并写入文件
    for (size_t i = 0; i < encodedStr.length(); i += 8) {
        string byteStr = encodedStr.substr(i, 8);
        if(byteStr.length() < 8){
            byteStr = byteStr + std::string(8 - byteStr.length(), '0');
        }
        bitset<8> bits(byteStr);
        
        outfile.put(static_cast<unsigned char>(bits.to_ulong()));
        
    }
}
void encodeFile2(const string& inputfile,const string& outputfile,const unordered_map<char, string>& code){
    ifstream infile(inputfile);
    ofstream outfile(outputfile,ios::binary);
    char ch;
    string encodedStr;
    //显示编码表
    
    /*for (const auto&pair : code){
        cout << pair.first << " : " << pair.second << endl;
    }*/
    //encodedStr为编码后的字符串,用Validlength记录有效编码长度
    int Validlength = 0;
    while(infile.get(ch)){
        encodedStr += code.at(ch);
    }
    
    //显示编码
    cout << "Encoded String: " << encodedStr << endl;
    
    // 将编码转换为字节并写入文件
    for (size_t i = 0; i < encodedStr.length(); i += 8) {
        string byteStr = encodedStr.substr(i, 8);
        if(byteStr.length() < 8){
            byteStr = byteStr + std::string(8 - byteStr.length(), '0');
        }
        bitset<8> bits(byteStr);
        
        outfile.put(static_cast<unsigned char>(bits.to_ulong()));
    }
}
//输入编码后的文件，输出解码后的文件，root为哈夫曼树的根节点
void decodeFile(const string& encodedFile,const string& decodedFile,HuffmanNode *root){
    ifstream infile(encodedFile,ios::binary);
    ofstream outfile(decodedFile);
    
    HuffmanNode* current = root;
    char byte;
    //读取有效位数
    int Validlength = 0;
    infile.read(reinterpret_cast<char*>(&Validlength), sizeof(Validlength));
    //读取编码后的字节并解码
    
    while(infile.get(byte)){
        bitset<8> bits(byte);
        for (int i = 7; i >= 0; --i) {
            Validlength--;
            if (Validlength < 0) {
                break;
            }
            if (bits[i] == 1) {
                current = current->right;
            } else {
                current = current->left;
            }
            if (current->left == nullptr && current->right == nullptr) {
                outfile.put(current->ch);
                current = root;
            }
        }
    }
}

// 定长编码解码，输入编码后的文件，编码表，输出解码后的文件
void decodeFile(const string& encodedFile, const string& decodedFile, const unordered_map<char, string>& code) {
    ifstream infile(encodedFile, ios::binary);
    ofstream outfile(decodedFile);

    // 获取固定编码的长度
    int codeLength = code.begin()->second.length();  // 所有字符编码长度相同

    // 创建反向编码表：从编码到字符的映射
    unordered_map<string, char> reverseCode;
    for (const auto& pair : code) {
        reverseCode[pair.second] = pair.first;
    }

    string bitStream = ""; // 存储所有读取的比特流
    char byte;
    while (infile.get(byte)) {
        // 将字节转为二进制字符串
        bitset<8> bits(byte);
        string byteBits = bits.to_string();  // 将字节转为8位二进制字符串

        // 将当前字节的比特流添加到总的比特流中
        bitStream += byteBits;

        // 每次读取codeLength长度的比特流
        while (bitStream.length() >= codeLength) {
            string currentCode = bitStream.substr(0, codeLength);  // 取出定长的比特流

            // 查表解码
            if (reverseCode.find(currentCode) != reverseCode.end()) {
                outfile.put(reverseCode[currentCode]);  // 输出对应的字符
                bitStream = bitStream.substr(codeLength);  // 移除已解码部分
            } else {
                // 如果没找到该编码，说明出错，应该停止或者进行错误处理
                cerr << "Error: Invalid encoding found in the bitstream!" << endl;
                return;
            }
        }
    }
}


int main(){
    /*
    //TestData::generateString(500,"testdata2.txt");
    //创建一个随机字符文件,testdata.txt
    //TestData::generateString(100);
    string inputfile = "testdata3.txt";
    //统计各字符个数
    unordered_map<char, int> fre = getCharFrequency(inputfile);
    //生成哈夫曼树
    HuffmanNode* root = BuildHuffmanTree(fre);
    //生成哈夫曼编码,code暂存当前节点编码，根节点为空""，Huffmancode存最终编码
    unordered_map<char, string> Huffmancode;
    generateHuffmancode(root, "",Huffmancode);
    //编码文件
    string encodefile = "encodedfile111.dat";
    encodeFile(inputfile,encodefile,Huffmancode);
    
    //解码文件
    
    string decodefile = "decodedfile111.txt";

    decodeFile(encodefile,decodefile,root);
    */

    //定长编码
    string inputfile = "testdata3.txt";
    //统计各字符个数
    unordered_map<char, int> fre = getCharFrequency(inputfile);
    unordered_map<char, string> fixedcode;
    generateFixedlengthcode(fixedcode, fre);
    string encodefile = "encodedfile222.dat";
    encodeFile2(inputfile,encodefile,fixedcode);
    string decodefile = "decodedfile222.txt";
    decodeFile(encodefile,decodefile,fixedcode);

    //对比编码前和解码后的文件是否一致
    std::ifstream original(inputfile), decoded(decodefile);
    if (original && decoded) {
        string originalStr((istreambuf_iterator<char>(original)), istreambuf_iterator<char>());
        string decodedStr((istreambuf_iterator<char>(decoded)), istreambuf_iterator<char>());
        if (originalStr == decodedStr) {
            cout << "解码正确，文件一致！" << endl;
        } else {
            cout << "解码失败，文件不一致。" << endl;
        }
    }
    return 0;
}