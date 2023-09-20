from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('home/', views.user_home_view, name='home'),
    path("register/", views.register_request, name="register"),
    path("packages/", views.user_packages_list, name='packages'),
    path("packages/<int:id>/detail",
         views.package_detial_view, name='package-detail'),
    path("packages/find/", views.PackageTrackView, name='package-find'),
    path("packages/bind/", views.PackageBindView, name='package-bind'),
    path("packages/<int:id>/update/", views.UpdateAddress, name='update'),
]
