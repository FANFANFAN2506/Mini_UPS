from django.urls import reverse
from django.db import models
from django.contrib.auth.models import User


class Truck(models.Model):
    truckid = models.IntegerField(primary_key=True, null=False)
    whid = models.IntegerField(null=True, blank=True)
    loca_x = models.IntegerField(null=False)
    loca_y = models.IntegerField(null=False)
    TRUCK_STATUS = (
        ('idle', 'idle'),
        ('traveling', 'traveling'),
        ('arrivewarehouse', 'arrivewarehouse'),
        ('delivering', 'delivering')
    )
    status = models.CharField(
        max_length=50,
        choices=TRUCK_STATUS,
        null=False,
        default='idle'
    )

    def __str__(self):
        return f"{self.truckid} {self.status} {self.whid}"

    def get_absolute_url(self):
        return reverse('model-detail-view', args=[str(self.TruckID)])


class Shipment(models.Model):
    packageid = models.IntegerField(primary_key=True, null=False)
    packagename = models.CharField(max_length=100, null=False)
    upsaccount = models.ForeignKey(
        User, on_delete=models.SET_NULL, null=True, blank=True, to_field='username')
    whid = models.IntegerField(null=False)
    dest_x = models.IntegerField(null=False)
    dest_y = models.IntegerField(null=False)
    PACKAGE_STATUS = (
        ('picking', 'picking'),
        ('loading', 'loading'),
        ('delivering', 'delivering'),
        ('arrived', 'arrived')
    )
    status = models.CharField(
        max_length=50,
        choices=PACKAGE_STATUS,
        null=False,
        default='created'
    )
    truck = models.ForeignKey(
        Truck, on_delete=models.SET_NULL, null=True, blank=True)

    def __str__(self):
        return f"{self.packageid} {self.packagename} {self.status}"

    def get_absolute_url(self):
        return reverse('package-detail', args=[str(self.packageid)])
