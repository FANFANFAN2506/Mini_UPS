import socket
import json
from django.shortcuts import render
from django.contrib.auth.decorators import login_required
from django.contrib.auth import login
from django.core.mail import send_mail
from django.http import HttpResponseRedirect
from django.urls import reverse_lazy, reverse
from django.contrib import messages
from .forms_ups import NewUserForm, FindPackageform, UpdateAddressform, BindPackageform
from django.views.generic.edit import UpdateView
from upsapp.models import Shipment, Truck
from django.contrib.auth.models import User
from django.shortcuts import get_object_or_404
# Create your views here.
SERVER_ADDR = "localhost"
PORT_NUM = 42345


def index(request):
    user_num = User.objects.all().count()
    shipment_num = Shipment.objects.all().count()
    dest_num = Shipment.objects.distinct("dest_x", "dest_y").count()
    return render(request, 'index.html', context={'user_num': user_num, 'shipment_num': shipment_num, "dest_num": dest_num})


def register_request(request):
    if request.method == "POST":
        form = NewUserForm(request.POST)
        if form.is_valid():
            user = form.save()
            login(request, user)
            messages.success(request, "Registration successful.")
            return HttpResponseRedirect(reverse('home'))
        messages.error(
            request, "Unsuccessful registration. Invalid information.")
    form = NewUserForm()
    return render(request=request, template_name="register.html", context={"register_form": form})


@login_required
def user_home_view(request):
    user_order_num = Shipment.objects.filter(
        upsaccount=request.user.username).count()
    user_dest_num = Shipment.objects.filter(
        upsaccount=request.user.username).distinct("dest_x", "dest_y").count()
    user_num = User.objects.all().count()
    shipment_num = Shipment.objects.all().count()
    dest_num = Shipment.objects.distinct("dest_x", "dest_y").count()
    average_shipment = shipment_num/user_num
    average_dest = dest_num/user_num
    context = {'average_shipment': average_shipment, 'average_dest': average_dest,
               'user_order_num': user_order_num, 'user_dest_num': user_dest_num}
    return render(request, 'user_home.html', context)


@login_required
def user_packages_list(request):
    owned_packages = Shipment.objects.filter(upsaccount=request.user.username)
    return render(request, 'ups/package_list.html', context={'owned_packages': owned_packages})


def package_detial_view(request, id):
    pack = get_object_or_404(Shipment, packageid=id)
    p_x = pack.dest_x
    p_y = pack.dest_y
    no_truck = False
    t_x = 0
    t_y = 0
    if pack.truck:
        truck = Truck.objects.filter(truckid=pack.truck.truckid).first()
        if truck == None or pack.status == 'arrived':
            no_truck = True
            t_x = truck.loca_x
            t_y = truck.loca_x
    if_modify = True
    if pack:
        if pack.status == "delivering" or pack.status == "arrived" or pack.upsaccount != request.user:
            if_modify = False
    logged = True
    context = {
        'packages': pack,
        'logged': logged,
        'if_modify': if_modify,
        'no_truck': no_truck,
        'p_x': p_x,
        'p_y': p_y,
        't_x': t_x,
        't_y': t_y,
    }
    return render(request, 'ups/package_detail.html', context)


def PackageTrackView(request):
    if request.method == "POST":
        form = FindPackageform(request.POST)
        if form.is_valid():
            tracknum = form.cleaned_data['trackingnum']
            pack = Shipment.objects.filter(packageid=tracknum).first()
            logged = True
            context = {
                'packages': pack,
                'logged': logged,
            }
            if pack:
                return package_detial_view(request, pack.packageid)
            else:
                return render(request, 'ups/package_detail.html', context)

    else:
        form = FindPackageform()
    context = {
        'form': form,
    }
    return render(request, 'ups/find_form.html', context)


@login_required
def PackageBindView(request):
    if request.method == "POST":
        form = BindPackageform(request.POST)
        if form.is_valid():
            tracknum = form.cleaned_data['trackingnum']
            productname = form.cleaned_data['packagename']
            pack = Shipment.objects.filter(packageid=tracknum).filter(
                packagename=productname).filter(upsaccount=None).first()
            if pack:
                pack.upsaccount = request.user
                pack.save()
            context = {
                'packages': pack,
            }
            return render(request, 'ups/bind_result.html', context)
    else:
        form = BindPackageform()
    context = {
        'form': form,
    }
    return render(request, 'ups/package_bind.html', context)


def UpdateAddress(request, id):
    pack = get_object_or_404(Shipment, packageid=id)
    if request.method == 'POST':
        form = UpdateAddressform(request.POST)
        if form.is_valid():
            new_x = form.cleaned_data['Destination_x']
            new_y = form.cleaned_data['Destination_y']
            # if_success = send_to_socket(id, new_x, new_y)
            pack = get_object_or_404(Shipment, packageid=id)
            if pack.status != "delivering" and pack.status != "arrived":
                pack.dest_x = new_x
                pack.dest_y = new_y
                pack.save()
                if pack.upsaccount != None:
                    print(pack.upsaccount.email)
                    send_mail(
                        'Congratulations!',
                        'Your package '+str(pack.packageid)+' name ' +
                        str(pack.packagename)+" destination has been changed to (" +
                        str(new_x)+","+str(new_y)+").",
                        'yangfan1670@163.com',
                        [pack.upsaccount.email],
                        fail_silently=False,
                    )
                return render(request, 'ups/package_detail.html', context={'packages': pack, 'logged': False})
            else:
                return render(request, 'ups/update_result.html', context={'packid': id})
    else:
        form = UpdateAddressform()
    context = {
        'packages': pack,
        'form': form,
    }
    return render(request, 'ups/update_address_form.html', context)


def send_to_socket(packageid, x, y):
    try:
        dict = {'id': packageid, 'x': x, 'y': y}
        json_str = json.dumps(dict)
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        s.connect((SERVER_ADDR, PORT_NUM))
        # data = str(pacakgeid).encode()
        s.sendall(json_str.encode())
        data = s.recv(1024)
        # 将JSON数据转换为Python对象
        json_data = json.loads(data)
        print(json_data["success"])
        s.close()
        return json_data["success"]
    except socket.error as e:
        print(f"Error connecting to socket: {e}")
        return None
