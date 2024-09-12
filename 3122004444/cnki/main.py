import difflib  # 使用difflib库中的方法来对文本进行查重
import sys      # 使用sys来接收命令函参数

# 根据命令行第二个和第三个参数得到目标的原文件和抄袭文件
with open(f'{sys.argv[1]}', 'r', encoding='utf-8')as file_original:
    paper_orin_content = file_original.read()
with open(f'{sys.argv[2]}', 'r', encoding='utf-8')as file_plagiarize:
    paper_plag_content = file_plagiarize.read()

# 对两个文件进行查重，将结果放入目标文件中
matcher = difflib.SequenceMatcher(None, paper_orin_content, paper_plag_content)
similarity_ratio = matcher.ratio()
with open(f'{sys.argv[3]}', 'a', encoding='utf-8')as file_anwser:
    file_anwser.write(format(similarity_ratio, '2f')+'\n')
