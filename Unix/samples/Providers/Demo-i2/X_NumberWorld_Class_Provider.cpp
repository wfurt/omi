/*
**==============================================================================
**
** Copyright (c) Microsoft Corporation. All rights reserved. See file LICENSE
** for license information.
**
**==============================================================================
*/

/* @migen@ */
#include <MI.h>
#include "X_NumberWorld_Class_Provider.h"
#include <stdlib.h>
#include <pal/strings.h>
#include <pal/format.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

MI_BEGIN_NAMESPACE

X_NumberWorld_Class_Provider::X_NumberWorld_Class_Provider(
        Module* module) :
    m_Module(module)
{
}

X_NumberWorld_Class_Provider::~X_NumberWorld_Class_Provider()
{
}

X_NumberWorld_Class GetNumberWorld(const String& ns)
{
    X_NumberWorld_Class inst;
    inst.Description_value(MI_T("<&\t xml-encoding-test \t&>"));
    inst.Name_value(MI_T("theWorld"));
    inst.Version_value(MI_T("0.1"));
    inst.ns_value(ns);
    inst.pid_value(getpid());

    /* user name */
    struct passwd* pwd = 0;
    char buf[1024];
    struct passwd current;

    if (0 == getpwuid_r(getuid(), &current, buf, sizeof(buf), &pwd) &&
        pwd &&
        pwd->pw_name)
    {
        MI_Char buf[128];
        TcsStrlcpy(buf, pwd->pw_name, sizeof(buf));
        inst.user_value(buf);
    }
    inst.uid_value(getuid());

    /* group name */
    struct group grbuf;
    struct group* gr;

    if (getgrgid_r(getgid(), &grbuf, buf, sizeof(buf), &gr) == 0  &&
        gr &&
        gr->gr_name)
    {
        MI_Char buf[128];
        TcsStrlcpy(buf, gr->gr_name, sizeof(buf));
        inst.group_value(buf);
    }
    inst.gid_value(getgid());
    inst.SetNamespace(MI_T("test/cpp"));
    return inst;
}

void X_NumberWorld_Class_Provider::EnumerateInstances(
    Context&  context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    context.Post(GetNumberWorld(nameSpace));
    context.Post(MI_RESULT_OK);
}

void X_NumberWorld_Class_Provider::GetInstance(
    Context&  context,
    const String& nameSpace,
    const X_NumberWorld_Class& instance_ref,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_NumberWorld_Class_Provider::CreateInstance(
    Context&  context,
    const String& nameSpace,
    const X_NumberWorld_Class& new_instance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_NumberWorld_Class_Provider::ModifyInstance(
    Context&  context,
    const String& nameSpace,
    const X_NumberWorld_Class& new_instance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_NumberWorld_Class_Provider::DeleteInstance(
    Context&  context,
    const String& nameSpace,
    const X_NumberWorld_Class& instance_ref)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_NumberWorld_Class_Provider::Invoke_Terminate(
    Context& context,
    const String& nameSpace,
    const X_NumberWorld_Class& instance,
    const X_NumberWorld_Terminate_Class& in)
{
    exit(1);
    //context.Post(MI_RESULT_NOT_SUPPORTED);
}

void X_NumberWorld_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_NumberWorld_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void X_NumberWorld_Class_Provider::Invoke_ReturnNamespace(
    Context& context,
    const String& nameSpace,
    const X_NumberWorld_Class& instanceName,
    const X_NumberWorld_ReturnNamespace_Class& in)
{
    X_NumberWorld_ReturnNamespace_Class out;

    out.MIReturn_value(nameSpace);
    context.Post(out);

    context.Post(MI_RESULT_OK);
}


MI_END_NAMESPACE
