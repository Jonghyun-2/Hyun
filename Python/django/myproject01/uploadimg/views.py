from django.shortcuts import render

# Create your views here.
def home(request):
    return render(request,'home.html')

def about(request):
    return render(request,'about.html')

# views.py에서 템플릿에서 전달하는 변수들을 request로 받아줌
# request는 name을 통해서 변수 전달

def result(request):
    # home.html : <textarea name='textarea'>
    # full = str
    test = request.GET['test']
    full = request.GET['fulltext']
    words = full.split()
    words_dic = {}
    for word in words:
        if word in words_dic:
            words_dic[word] +=1
        else:
            words_dic[word] = 1
    # render 에서 parameter를 dict 형태로 전달해줄경우
    return render(request, 'result.html',
                  {'full':full,'length':len(words),'dic':words_dic.items(),'test':test})