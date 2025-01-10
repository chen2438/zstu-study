import pandas as pd

# 读取Excel文件，获取所有工作表的数据
dfs = pd.read_excel('E:\\学习\\大三上\\python\\top_movies.xlsx', sheet_name=None)

# 获取所有表名
sheet_names = list(dfs.keys())
sheet_names

# 假设你要处理的工作表名为'Sheet1'，可以根据实际情况修改
df = dfs['Sheet1']

# 去除票房数据中的逗号
df['Box Office'] = df['Box Office'].str.replace(',', '')

# 将票房数据转换为数值类型
df['Box Office'] = pd.to_numeric(df['Box Office'])

# 读取Sheet1数据
data = df

print('数据基本信息：')
data.info()
print('数据的前几行：')
print(data.head())

# 进行去重，得到去重数据data
# 对Title列进行分组，计算每组中Box Office列的总和
group_data = data.groupby('Title')['Box Office'].sum().reset_index()

# 合并
data = pd.merge(data.drop_duplicates(subset='Title'), group_data, on='Title')

# 按照上映年份进行分组，并计算每年的票房总和
yearly_box_office = df.groupby('Year')['Box Office'].sum().reset_index()

# 分析电影类型的分布情况
genre_distribution = data['Genres'].value_counts()

# 找出票房排名前五十的电影（根据处理后的票房重新排名）
# 这里将排序的列名改为合并后正确的列名 'Box Office_y'
top_50_movies = data.sort_values('Box Office_y', ascending=False).head(50).reset_index()
top_50_movies['rank'] = range(1, 51)
top_50_movies = top_50_movies[['rank', 'Title', 'Box Office_y', 'Release Date', 'Year']]
top_50_movies.columns = ['rank', 'movie_name', 'box_office', 'release_date', 'year']

# 分析电影上映日期与票房的关系
release_date_box_office = data.groupby('Release Date')['Box Office_y'].sum()

# 对电影票房进行分类
def classify_box_office(box_office):
    if box_office >= 10000000:
        return '一千万以上'
    elif box_office >= 5000000:
        return '五百万以上'
    elif box_office >= 1000000:
        return '一百万以上'
    else:
        return '一百万以下'

data['Box Office Class'] = data['Box Office_y'].apply(classify_box_office)
box_office_classification = data['Box Office Class'].value_counts()

# 对电影发布日期分类
def classify_release_date(release_date):
    month = pd.to_datetime(release_date).month
    if month in [1, 2, 3]:
        return '第一季度'
    elif month in [4, 5, 6]:
        return '第二季度'
    elif month in [7, 8, 9]:
        return '第三季度'
    else:
        return '第四季度'

data['Release Date Class'] = data['Release Date'].apply(classify_release_date)
release_date_classification = data['Release Date Class'].value_counts()

# 对电影发布日期和电影类型进行分类
release_date_genre_classification = data.groupby(['Release Date Class', 'Genres']).size().reset_index(name='数量')

# 创建一个新的Excel文件
wb = pd.ExcelWriter('E:\\学习\\大三上\\python\\top_movies_analysis_charts.xlsx', engine='xlsxwriter')

# 将数据写入相应的工作表
yearly_box_office.to_excel(wb, sheet_name='每年票房总和', index=False)
genre_distribution.to_excel(wb, sheet_name='电影类型分布情况', index=True)
top_50_movies.to_excel(wb, sheet_name='票房排名前五十的电影', index=False)
release_date_box_office.to_excel(wb, sheet_name='电影上映日期与票房的关系', index=True)
box_office_classification.to_excel(wb, sheet_name='电影票房分类', index=True)
release_date_classification.to_excel(wb, sheet_name='电影发布日期分类', index=True)
release_date_genre_classification.to_excel(wb, sheet_name='电影发布日期和电影类型分类', index=False)

# 获取工作簿对象
workbook = wb.book

# 创建一个新的图表工作表
chart_sheet = workbook.add_worksheet('图表')

# 创建每年票房总和折线图
chart_yearly_box_office = workbook.add_chart({'type': 'line'})
chart_yearly_box_office.add_series({
    'name': '票房总和',
    'categories': '=每年票房总和!$A$2:$A$' + str(yearly_box_office.shape[0] + 1),
    'values': '=每年票房总和!$B$2:$B$' + str(yearly_box_office.shape[0] + 1)
})
chart_yearly_box_office.set_title({'name': '每年票房总和'})
chart_yearly_box_office.set_x_axis({'name': '年份'})
chart_yearly_box_office.set_y_axis({'name': '票房总和'})
chart_sheet.insert_chart('A1', chart_yearly_box_office)

# 创建电影类型分布情况饼图
chart_genre_distribution = workbook.add_chart({'type': 'pie'})
chart_genre_distribution.add_series({
    'name': '电影类型分布情况',
    'categories': '=电影类型分布情况!$A$2:$A$' + str(genre_distribution.shape[0] + 1),
    'values': '=电影类型分布情况!$B$2:$B$' + str(genre_distribution.shape[0] + 1)
})
chart_genre_distribution.set_title({'name': '电影类型分布情况'})

# 设置饼图的数据标签格式，显示类别名称、值和百分比
data_labels_format = {
    'num_format': '0.00%',  # 设置百分比格式，保留两位小数
    'font': {'name': '宋体', 'size': 9},  # 设置字体为宋体，大小为9
    'border': {'color': 'black'},  # 设置边框颜色为黑色
    'fill': {'color': 'white'},  # 设置背景颜色为白色
}
chart_genre_distribution.set_legend({'value': True, 'category': True, 'percentage': True, 'data_labels_format': data_labels_format})
chart_sheet.insert_chart('A20', chart_genre_distribution)

# 创建电影票房分类饼图
chart_box_office_classification = workbook.add_chart({'type': 'pie'})
chart_box_office_classification.add_series({
    'name': '电影票房分类',
    'categories': '=电影票房分类!$A$2:$A$' + str(box_office_classification.shape[0] + 1),
    'values': '=电影票房分类!$B$2:$B$' + str(box_office_classification.shape[0] + 1)
})
chart_box_office_classification.set_title({'name': '电影票房分类'})

# 设置饼图的数据标签格式，显示类别名称、值和百分比
data_labels_format = {
    'num_format': '0.00%',  # 设置百分比格式，保留两位小数
    'font': {'name': '宋体', 'size': 9},  # 设置字体为宋体，大小为9
    'border': {'color': 'black'},  # 设置边框颜色为黑色
    'fill': {'color': 'white'},  # 设置背景颜色为白色
}
chart_box_office_classification.set_legend({'value': True, 'category': True, 'percentage': True, 'data_labels_format': data_labels_format})
chart_sheet.insert_chart('A40', chart_box_office_classification)

# 创建电影发布日期分类柱状图
chart_release_date_classification = workbook.add_chart({'type': 'bar'})
chart_release_date_classification.add_series({
    'name': '电影数量',
    'categories': '=电影发布日期分类!$A$2:$A$' + str(release_date_classification.shape[0] + 1),
    'values': '=电影发布日期分类!$B$2:$B$' + str(release_date_classification.shape[0] + 1)
})
chart_release_date_classification.set_title({'name': '电影发布日期分类'})
chart_release_date_classification.set_x_axis({'name': '季度'})
chart_release_date_classification.set_y_axis({'name': '电影数量'})
chart_sheet.insert_chart('A60', chart_release_date_classification)

# 创建电影发布日期和电影类型分类柱状图
chart_release_date_genre_classification = workbook.add_chart({'type': 'bar'})
for genre in release_date_genre_classification['Genres'].unique():
    genre_data = release_date_genre_classification[release_date_genre_classification['Genres'] == genre]
    chart_release_date_genre_classification.add_series({
        'name': genre,
        'categories': '=电影发布日期和电影类型分类!$A$2:$A$' + str(genre_data.shape[0] + 1),
        'values': '=电影发布日期和电影类型分类!$C$2:$C$' + str(genre_data.shape[0] + 1)
    })
chart_release_date_genre_classification.set_title({'name': '电影发布日期和电影类型分类'})
chart_release_date_genre_classification.set_x_axis({'name': '季度'})
chart_release_date_genre_classification.set_y_axis({'name': '电影数量'})
chart_release_date_genre_classification.set_legend({'position': 'right'})
chart_sheet.insert_chart('A80', chart_release_date_genre_classification)

# 保存Excel文件
wb.close()
