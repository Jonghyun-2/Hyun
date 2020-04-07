from django.shortcuts import render, get_object_or_404
from .models import Blog

# Create your views here.

def home(request):
    blog = Blog.objects
    return render(request, 'home.html', {'blogs':blog})

def detail(request, blog_id):
    blog_detail = get_object_or_404(Blog,pk=blog_id)
    return render(request, 'detail.html',{'blog': blog_detail})

def test(request):
    blog = Blog.objects
    return render(request,'test.html',{'blog':blog})