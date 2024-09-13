import difflib  # 使用difflib库中的方法来对文本进行查重


class Cnki:
    def __init__(self, file_ori, filen_pla, file_res):
        self.file_ori = file_ori
        self.filen_pla = filen_pla
        self.file_res = file_res

    # 利用文件并处理不正常参数
    def jud_inp(self):
        try:
            with open(f'{self.file_ori}', 'r', encoding='utf-8') as file_original:
                self.paper_orin_content = file_original.read()
            with open(f'{self.filen_pla}', 'r', encoding='utf-8') as file_plagiarize:
                self.paper_plag_content = file_plagiarize.read()

        except FileNotFoundError:
            print("请输入正确的文件路径")
            return FileNotFoundError

    # 进行查重并写入目标文件
    def cnki(self):
        if(self.jud_inp()==FileNotFoundError):
            return FileNotFoundError
        # 根据命令行第二个和第三个参数得到目标的原文件和抄袭文件
        matcher = difflib.SequenceMatcher(None, self.paper_orin_content, self.paper_plag_content)
        # 对两个文件进行查重，将结果放入目标文件中
        similarity_ratio = matcher.ratio()
        try:
            with open(f'{self.file_res}', 'a', encoding='utf-8') as file_anwser:
                file_anwser.write(format(similarity_ratio, '2f')+'\n')
        except FileNotFoundError:
            print("请输入正确的文件路径")
            return FileNotFoundError