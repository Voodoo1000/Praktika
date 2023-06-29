object Form1: TForm1
  Left = 0
  Top = 0
  Caption = #1044#1086#1073#1072#1074#1080#1090#1100
  ClientHeight = 197
  ClientWidth = 228
  Color = clCream
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 23
    Top = 19
    Width = 44
    Height = 13
    Caption = #1060#1072#1084#1080#1083#1080#1103
  end
  object Label2: TLabel
    Left = 5
    Top = 57
    Width = 88
    Height = 13
    Caption = #1054#1094#1077#1085#1082#1072' '#1079#1072' 1 '#1083#1072#1073#1091
  end
  object Label3: TLabel
    Left = 3
    Top = 95
    Width = 88
    Height = 13
    Caption = #1054#1094#1077#1085#1082#1072' '#1079#1072' 2 '#1083#1072#1073#1091
  end
  object Label4: TLabel
    Left = 3
    Top = 133
    Width = 88
    Height = 13
    Caption = #1054#1094#1077#1085#1082#1072' '#1079#1072' 3 '#1083#1072#1073#1091
  end
  object Edit1: TEdit
    Left = 99
    Top = 16
    Width = 121
    Height = 21
    TabOrder = 0
    OnExit = Edit1Exit
    OnKeyDown = Edit1KeyDown
  end
  object Edit2: TEdit
    Left = 99
    Top = 54
    Width = 121
    Height = 21
    TabOrder = 1
    OnExit = Edit2Exit
    OnKeyDown = Edit2KeyDown
  end
  object Edit3: TEdit
    Left = 97
    Top = 92
    Width = 121
    Height = 21
    TabOrder = 2
    OnExit = Edit3Exit
    OnKeyDown = Edit3KeyDown
  end
  object Button1: TButton
    Left = 56
    Top = 164
    Width = 105
    Height = 25
    Caption = #1044#1086#1073#1072#1074#1080#1090#1100
    TabOrder = 3
    OnClick = ButtonClick
  end
  object Edit4: TEdit
    Left = 97
    Top = 130
    Width = 121
    Height = 21
    TabOrder = 4
    OnExit = Edit4Exit
    OnKeyDown = Edit4KeyDown
  end
end
