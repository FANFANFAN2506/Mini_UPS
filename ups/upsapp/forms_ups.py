from django.core.exceptions import ValidationError
from django import forms
from django.contrib.auth.forms import UserCreationForm
from django.contrib.auth.models import User
from django.utils.translation import gettext_lazy as _


class NewUserForm(UserCreationForm):
    email = forms.EmailField(required=True)

    class Meta:
        model = User
        fields = ("username", "email", "password1", "password2")

    def save(self, commit=True):
        user = super(NewUserForm, self).save(commit=False)
        user.email = self.cleaned_data['email']
        if commit:
            user.save()
        return user


class FindPackageform(forms.Form):
    trackingnum = forms.CharField(
        required=True, max_length=100, help_text="Please input the tracking number")


class BindPackageform(forms.Form):
    trackingnum = forms.CharField(
        required=True, max_length=100, help_text="Please input the tracking number")
    packagename = forms.CharField(
        required=True, max_length=100, help_text="Please input the product name to verify")


class UpdateAddressform(forms.Form):
    Destination_x = forms.IntegerField(
        required=True, help_text="Input the new address x coordination")
    Destination_y = forms.IntegerField(
        required=True, help_text="Input the new address y coordination")

    def clean_Destination_x(self):
        data = self.cleaned_data['Destination_x']
        if data < 0:
            raise ValidationError(
                _('Destination must be non-negative'))
        return data

    def clean_Destination_y(self):
        data = self.cleaned_data['Destination_y']
        if data < 0:
            raise ValidationError(
                _('Destination must be non-negative'))
        return data
